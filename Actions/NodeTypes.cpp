#include "Actions/SequenceNode.h"
#include "Actions/ConcurrentNode.h"
#include "Actions/TicketAcquisitionNode.h"
#include "Actions/TreeChopNode.h"
#include "Actions/TargetReachNode.h"
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

    void setupConcurrent() {
      NodeInterface interface;
      interface.start = ConcurrentNode::start;
      interface.calcConfigLength = ConcurrentNode::calcConfigLength;
      interface.calcStateLength = ConcurrentNode::calcStateLength;
      interface.configure = ConcurrentNode::configure;
      interface.isCompleted = ConcurrentNode::isCompleted;
      Node::setup(NodeTypeIndex::Concurrent, &interface);
    }

    void setupTicketAcquisition() {
      NodeInterface interface;
      interface.start = TicketAcquisitionNode::start;
      interface.calcConfigLength = TicketAcquisitionNode::calcConfigLength;
      interface.calcStateLength = TicketAcquisitionNode::calcStateLength;
      interface.configure = TicketAcquisitionNode::configure;
      interface.isCompleted = TicketAcquisitionNode::isCompleted;
      Node::setup(NodeTypeIndex::TicketAcquisition, &interface);
    }

    void setupTreeChop() {
      NodeInterface interface;
      interface.start = TreeChopNode::start;
      interface.calcConfigLength = TreeChopNode::calcConfigLength;
      interface.calcStateLength = TreeChopNode::calcStateLength;
      interface.configure = TreeChopNode::configure;
      interface.isCompleted = TreeChopNode::isCompleted;
      Node::setup(NodeTypeIndex::TreeChop, &interface);
    }

    void setupTargetReach() {
      NodeInterface interface;
      interface.start = TargetReachNode::start;
      interface.calcConfigLength = TargetReachNode::calcConfigLength;
      interface.calcStateLength = TargetReachNode::calcStateLength;
      interface.configure = TargetReachNode::configure;
      interface.isCompleted = TargetReachNode::isCompleted;
      Node::setup(NodeTypeIndex::TargetReach, &interface);
    }

    void setup() {
      setupSequence();
      setupConcurrent();
      setupTicketAcquisition();
      setupTreeChop();
      setupTargetReach();
    }
  }
}
