#include "Watson/Node.h"
#include "Watson/NodeTypes.h"
#include "Watson/TypeIndex.h"
#include "Watson/TypeDefinition.h"
#include "Watson/TypeList.h"
#include "Watson/InstanceOrderingCollection.h"
#include "Watson/StateCollection.h"
#include "Watson/ActionStreamCollection.h"
#include "Watson/BoardCollection.h"
#include "Watson/InstanceHandle.h"
#include "Watson/TypeList.h"
#include "Watson/InstanceList.h"
#include "Watson/Update.h"

namespace Watson {
  namespace System {
    void initialize() {
      NodeTypes::initialize();
    }

    TypeIndex createType(const TypeDefinition *definition) {
      TypeIndex index = TypeList::create(definition);
      InstanceOrderingCollection::createList(index, definition->instanceMax);
      StateCollection::createList(index);
      BoardCollection::createList(index);
      ActionStreamCollection::createList(index);
      return index;
    }

    uint8_t getTypeCount() {
      return TypeList::getCount();
    }

    uint16_t getInstanceCount(TypeIndex typeIndex) {
      return InstanceOrderingCollection::getCount(typeIndex);
    }

    InstanceHandle createInstance(TypeIndex typeIndex) {
      InstanceOrderingHandle instanceOrderingHandle;
      uint16_t instanceIndex;
      InstanceOrderingCollection::create(typeIndex, &instanceOrderingHandle, &instanceIndex);

      uint16_t nodeCount = TypeList::getNodeCount(typeIndex);
      for(uint16_t i=0; i<nodeCount; ++i) {
        const void *nodeStructure = TypeList::getStructureNode(typeIndex, i);
        void *nodeState = StateCollection::getNode(typeIndex, instanceIndex, i);
        Node::initializeState(nodeStructure, nodeState);
      }

      InstanceHandle treeHandle = InstanceList::create(typeIndex, instanceOrderingHandle);
      return treeHandle;
    }

    Board* getBoardByIndices(TypeIndex typeIndex, uint16_t instanceIndex) {
      return BoardCollection::get(typeIndex, instanceIndex);
    }

    Board* getBoardByHandle(InstanceHandle treeHandle) {
      TypeIndex typeIndex = InstanceList::getTypeIndex(treeHandle);
      InstanceOrderingHandle instanceOrderingHandle = InstanceList::getInstanceOrderingHandle(treeHandle);
      uint16_t instanceIndex = InstanceOrderingCollection::getIndex(typeIndex, instanceOrderingHandle);
      return getBoardByIndices(typeIndex, instanceIndex);
    }

    Stream* getActionStream(TypeIndex typeIndex, uint16_t instanceIndex) {
      return ActionStreamCollection::get(typeIndex, instanceIndex);
    }

    void destroyTree(InstanceHandle handle) {
      TypeIndex typeIndex = InstanceList::getTypeIndex(handle);
      InstanceOrderingHandle instanceOrderingHandle = InstanceList::getInstanceOrderingHandle(handle);

      uint16_t sourceInstanceIndex;
      uint16_t destinationInstanceIndex;
      InstanceOrderingCollection::destroy(
        typeIndex,
        instanceOrderingHandle,
        &sourceInstanceIndex,
        &destinationInstanceIndex
      );
      BoardCollection::move(typeIndex, sourceInstanceIndex, destinationInstanceIndex);
      StateCollection::move(typeIndex, sourceInstanceIndex, destinationInstanceIndex);

      InstanceList::destroy(handle);
    }

    void update() {
      for(TypeIndex i=0; i<TypeList::getCount(); ++i) {
        // todo: prefetch structureOffset or something like it here
        uint16_t instanceCount = InstanceOrderingCollection::getCount(i);
        for(uint16_t n=0; n<instanceCount; ++n) {
          Update::run(i, n);
        }
      }

      for(TypeIndex i=0; i<TypeList::getCount(); ++i) {
        uint16_t instanceCount = InstanceOrderingCollection::getCount(i);
        for(uint16_t n=0; n<instanceCount; ++n) {
          BoardCollection::get(i, n)->clear();
        }
      }
    }

    void clearActionStreams() {
      for(TypeIndex i=0; i<TypeList::getCount(); ++i) {
        uint16_t instanceCount = InstanceOrderingCollection::getCount(i);
        for(uint16_t n=0; n<instanceCount; ++n) {
          ActionStreamCollection::get(i, n)->clear();
        }
      }
    }
  }
}
