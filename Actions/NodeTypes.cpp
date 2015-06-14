#include "Actions/SequenceNode.h"
#include "Actions/TreeLocalizationNode.h"
#include "Actions/NodeTypeIndex.h"
#include "Actions/Node.h"
#include "Actions/NodeInterface.h"
#include "Actions/NodeTypes.h"

namespace Actions {
  namespace NodeTypes {
    void setupSequence() {
      NodeInterface interface;
      interface.start = SequenceNode::start;
      interface.calcConfigLength = SequenceNode::calcConfigLength;
      interface.calcStateLength = SequenceNode::calcStateLength;
      interface.configure = SequenceNode::configure;
      interface.isCompleted = SequenceNode::isCompleted;
      Node::setup(NodeTypeIndex::Sequence, &interface);
    }

    void setupTreeLocalization() {
      NodeInterface interface;
      interface.start = TreeLocalizationNode::start;
      interface.calcConfigLength = TreeLocalizationNode::calcConfigLength;
      interface.calcStateLength = TreeLocalizationNode::calcStateLength;
      interface.configure = TreeLocalizationNode::configure;
      interface.isCompleted = TreeLocalizationNode::isCompleted;
      Node::setup(NodeTypeIndex::TreeLocalization, &interface);
    }

    void setup() {
      setupSequence();
      setupTreeLocalization();
    }
  }
}
