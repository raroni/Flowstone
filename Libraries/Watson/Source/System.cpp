#include "Watson/Node.h"
#include "Watson/NodeInterface.h"
#include "Watson/NodeType.h"
#include "Watson/PriorityNode.h"
#include "Watson/ConcurrentNode.h"
#include "Watson/TypeIndex.h"
#include "Watson/TypeDefinition.h"
#include "Watson/TypeList.h"
#include "Watson/InstanceOrderingCollection.h"
#include "Watson/StateCollection.h"
#include "Watson/BoardCollection.h"
#include "Watson/InstanceHandle.h"
#include "Watson/TypeList.h"
#include "Watson/InstanceList.h"
#include "Watson/Update.h"

namespace Watson {
  namespace System {
    void setupNodeInterface(NodeType type, NodeInterface interface) {
      Node::setupInterface(static_cast<uint8_t>(type), interface);
    }

    void initialize() {
      NodeInterface priorityInterface = {
        .enter = PriorityNode::enter,
        .react = PriorityNode::react,
        .reset = PriorityNode::reset,
        .initializeState = PriorityNode::initializeState
      };
      setupNodeInterface(NodeType::Priority, priorityInterface);

      NodeInterface concurrentInterface = {
        .enter = ConcurrentNode::enter,
        .react = ConcurrentNode::react,
        .reset = PriorityNode::reset,
        .initializeState = ConcurrentNode::initializeState
      };
      setupNodeInterface(NodeType::Concurrent, concurrentInterface);
    }

    TypeIndex createType(const TypeDefinition *definition) {
      TypeIndex index = TypeList::create(definition);
      InstanceOrderingCollection::createList(index, definition->instanceMax);
      StateCollection::createList(index);
      BoardCollection::createList(index);
      return index;
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

    Board* getBoard(InstanceHandle treeHandle) {
      TypeIndex typeIndex = InstanceList::getTypeIndex(treeHandle);
      InstanceOrderingHandle instanceOrderingHandle = InstanceList::getInstanceOrderingHandle(treeHandle);
      uint16_t instanceIndex = InstanceOrderingCollection::getIndex(typeIndex, instanceOrderingHandle);
      return BoardCollection::get(typeIndex, instanceIndex);
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
    }
  }
}
