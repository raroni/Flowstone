#include "Actions/NodeStructureHeader.h"
#include "Actions/TreeLocalizationNode.h"
#include "Actions/SequenceNode.h"
#include "Actions/ConcurrentNode.h"
#include "Actions/ActionTypeDefinitionHelper.h"

namespace Actions {
  typedef ActionTypeDefinitionHelper ATDH;

  ATDH::ActionTypeDefinitionHelper(ActionTypeDefinition *definition) :
  definition(definition) { }

  void ATDH::setInstanceMax(uint8_t max) {
    definition->instanceMax = max;
  }

  NodeIndex ATDH::writeSequence(uint8_t childCount) {
    SequenceNode::CreationArgSet args;
    args.childCount = childCount;
    return definition->createNode(NodeTypeIndex::Sequence, &args);
  }

  NodeIndex ATDH::writeConcurrent(uint8_t childCount) {
    ConcurrentNode::CreationArgSet args;
    args.childCount = childCount;
    return definition->createNode(NodeTypeIndex::Concurrent, &args);
  }

  void ATDH::configureSequence(NodeIndex sequenceNode, uint8_t childCount, NodeIndex *children) {
    SequenceNode::ConfigArgSet args = {
      .childCount = childCount,
      .children = children
    };
    definition->configureNode(sequenceNode, &args);
  }

  void ATDH::configureConcurrent(NodeIndex concurrentNode, uint8_t childCount, NodeIndex *children) {
    ConcurrentNode::ConfigArgSet args = {
      .childCount = childCount,
      .children = children
    };
    definition->configureNode(concurrentNode, &args);
  }

  NodeIndex ATDH::writeTreeLocalization() {
    return definition->createNode(NodeTypeIndex::TreeLocalization, nullptr);
  }

  NodeIndex ATDH::writeTreeChop() {
    return definition->createNode(NodeTypeIndex::TreeChop, nullptr);
  }

  NodeIndex ATDH::writeTargetReach() {
    return definition->createNode(NodeTypeIndex::TargetReach, nullptr);
  }
}
