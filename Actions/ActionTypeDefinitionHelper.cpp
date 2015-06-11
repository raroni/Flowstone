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

  ATDH::Creation ATDH::create(NodeTypeIndex type, uint8_t configLength, uint8_t stateLength) {
    Creation creation;
    creation.index = definition->createNode(type, configLength, stateLength);
    creation.config = getConfig(creation.index);
    return creation;
  }

  void* ATDH::getConfig(NodeIndex index) {
    char *nodeStructure = static_cast<char*>(definition->getNodeStructure(index));
    return nodeStructure+sizeof(NodeStructureHeader);
  }

  NodeIndex ATDH::writeSequence(uint8_t childCount) {
    Creation creation = create(
      NodeTypeIndex::Sequence,
      SequenceNode::calcConfigLength(childCount),
      SequenceNode::stateLength
    );
    SequenceNode::writeConfig(creation.config, childCount);
    return creation.index;
  }

  NodeIndex ATDH::writeTreeLocalization() {
    Creation creation = create(
      NodeTypeIndex::TreeLocalization,
      TreeLocalizationNode::configLength,
      TreeLocalizationNode::stateLength
    );
    return creation.index;
  }
}
