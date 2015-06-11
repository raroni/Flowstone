#include "Actions/SequenceNode.h"
#include "Actions/NodeTypeIndex.h"
#include "Actions/Node.h"
#include "Actions/NodeInterface.h"
#include "Actions/NodeTypes.h"

namespace Actions {
  namespace NodeTypes {
    void setupSequence() {
      NodeInterface interface = {
        .start = SequenceNode::start
      };
      Node::setup(NodeTypeIndex::Sequence, &interface);
    }

    void setupTreeLocalization() {
      NodeInterface interface = {
        .start = SequenceNode::start
      };
      Node::setup(NodeTypeIndex::Sequence, &interface);
    }

    void setup() {
      setupSequence();
      setupTreeLocalization();
    }
  }
}
