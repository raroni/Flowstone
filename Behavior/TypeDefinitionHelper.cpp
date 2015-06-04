#include "Watson/PriorityNode.h"
#include "Watson/ConcurrentNode.h"
#include "Watson/FailDummyNode.h"
#include "Watson/RunDummyNode.h"
#include "Behavior/ThreatCheckNode.h"
#include "Behavior/TypeDefinitionHelper.h"

namespace Behavior {
  typedef TypeDefinitionHelper TDH;
  typedef Watson::NodeIndex NodeIndex;
  namespace PriorityNode = Watson::PriorityNode;
  namespace ConcurrentNode = Watson::ConcurrentNode;
  namespace FailDummyNode = Watson::FailDummyNode;
  namespace RunDummyNode = Watson::RunDummyNode;

  TDH::TypeDefinitionHelper(Watson::TypeDefinition *definition) :
  definition(definition) { }

  void* TDH::getStructureNode(NodeIndex index) {
    return definition->getStructureNode(index);
  }

  TDH::Creation TDH::create(uint8_t type, uint16_t structureLength, uint16_t stateLength) {
    Creation creation;
    creation.index = definition->createNode(type, structureLength, stateLength);
    creation.structureNode = getStructureNode(creation.index);
    return creation;
  }

  TDH::Creation TDH::createWatson(Watson::NodeType type, uint16_t structureLength, uint16_t stateLength) {
    return create(
      static_cast<uint8_t>(type),
      structureLength,
      stateLength
    );
  }

  TDH::Creation TDH::createCustom(NodeType type, uint16_t structureLength, uint16_t stateLength) {
    return create(
      static_cast<uint8_t>(type),
      structureLength,
      stateLength
    );
  }

  NodeIndex TDH::writePriority(uint8_t childCount) {
    Creation creation = createWatson(
      Watson::NodeType::Priority,
      PriorityNode::calcStructureLength(childCount),
      PriorityNode::calcStateLength(childCount)
    );
    PriorityNode::writeStructure(creation.structureNode, childCount);
    return creation.index;
  }

  NodeIndex TDH::writeFailDummy() {
    Creation creation = createWatson(
      Watson::NodeType::FailDummy,
      FailDummyNode::structureLength,
      FailDummyNode::stateLength
    );
    return creation.index;
  }

  NodeIndex TDH::writeRunDummy() {
    Creation creation = createWatson(
      Watson::NodeType::RunDummy,
      RunDummyNode::structureLength,
      RunDummyNode::stateLength
    );
    return creation.index;
  }

  NodeIndex TDH::writeThreatCheck() {
    Creation creation = createCustom(
      NodeType::ThreatCheck,
      ThreatCheckNode::structureLength,
      ThreatCheckNode::stateLength
    );
    return creation.index;
  }

  NodeIndex TDH::writeConcurrent(uint8_t childCount) {
    Creation creation = createWatson(
      Watson::NodeType::Concurrent,
      ConcurrentNode::calcStructureLength(childCount),
      ConcurrentNode::calcStateLength(childCount)
    );
    ConcurrentNode::writeStructure(creation.structureNode, childCount);
    return creation.index;
  }

  void TDH::setInstanceMax(uint16_t max) {
    definition->instanceMax = max;
  }

  void TDH::setPriorityChild(NodeIndex priorityIndex, uint8_t childSlot, NodeIndex childIndex) {
    void *node = getStructureNode(priorityIndex);
    PriorityNode::setChild(node, childSlot, childIndex);
  }

  void TDH::setConcurrentChild(NodeIndex concurrentIndex, uint8_t childSlot, NodeIndex childIndex) {
    void *node = getStructureNode(concurrentIndex);
    ConcurrentNode::setChild(node, childSlot, childIndex);
  }
}
