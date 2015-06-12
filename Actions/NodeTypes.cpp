#include "Actions/SequenceNode.h"
#include "Actions/TreeLocalizationNode.h"
#include "Actions/NodeTypeIndex.h"
#include "Actions/Node.h"
#include "Actions/NodeInterface.h"
#include "Actions/NodeTypes.h"

namespace Actions {
  namespace NodeTypes {
    void setupSequence() {
      NodeInterface interface = {
        .start = SequenceNode::start,
        .calcConfigLength = SequenceNode::calcConfigLength,
        .calcStateLength = SequenceNode::calcStateLength,
        .configure = SequenceNode::configure
      };
      Node::setup(NodeTypeIndex::Sequence, &interface);
    }

    void setupTreeLocalization() {
      NodeInterface interface = {
        .start = TreeLocalizationNode::start,
        .calcConfigLength = TreeLocalizationNode::calcConfigLength,
        .calcStateLength = TreeLocalizationNode::calcStateLength,
        .configure = TreeLocalizationNode::configure
      };
      Node::setup(NodeTypeIndex::TreeLocalization, &interface);
    }

    void setup() {
      setupSequence();
      setupTreeLocalization();
    }
  }
}
