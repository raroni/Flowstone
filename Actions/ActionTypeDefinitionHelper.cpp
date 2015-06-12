#include "Actions/NodeStructureHeader.h"
#include "Actions/TreeLocalizationNode.h"
#include "Actions/SequenceNode.h"
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

  void ATDH::configureSequence(NodeIndex sequenceNode, uint8_t childCount, NodeIndex *children) {
    SequenceNode::ConfigArgSet args = {
      .childCount = childCount,
      .children = children
    };
    definition->configureNode(sequenceNode, &args);
  }

  NodeIndex ATDH::writeTreeLocalization() {
    return definition->createNode(NodeTypeIndex::TreeLocalization, nullptr);
  }
}
