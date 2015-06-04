#include "Watson/NodeType.h"
#include "Watson/PriorityNode.h"
#include "Watson/ConcurrentNode.h"
#include "Watson/LoopNode.h"
#include "Watson/FailDummyNode.h"
#include "Watson/RunDummyNode.h"
#include "Watson/Node.h"
#include "Watson/NodeTypes.h"

namespace Watson {
  namespace NodeTypes {
    void setup(NodeType type, NodeInterface interface) {
      Node::setupInterface(static_cast<uint8_t>(type), interface);
    }

    void setupPriority() {
      NodeInterface interface = {
        .enter = PriorityNode::enter,
        .react = PriorityNode::react,
        .reset = PriorityNode::reset,
        .initializeState = PriorityNode::initializeState
      };
      setup(NodeType::Priority, interface);
    }

    void setupConcurrent() {
      NodeInterface interface = {
        .enter = ConcurrentNode::enter,
        .react = ConcurrentNode::react,
        .reset = ConcurrentNode::reset,
        .initializeState = ConcurrentNode::initializeState
      };
      setup(NodeType::Concurrent, interface);
    }

    void setupLoop() {
      NodeInterface interface = {
        .enter = LoopNode::enter,
        .react = LoopNode::react,
        .reset = LoopNode::reset,
        .initializeState = LoopNode::initializeState
      };
      setup(NodeType::Loop, interface);
    }

    void setupFailDummy() {
      NodeInterface interface = {
        .enter = FailDummyNode::enter,
        .reset = FailDummyNode::reset,
        .initializeState = FailDummyNode::initializeState
      };
      setup(NodeType::FailDummy, interface);
    }

    void setupRunDummy() {
      NodeInterface interface = {
        .enter = RunDummyNode::enter,
        .reset = RunDummyNode::reset,
        .initializeState = RunDummyNode::initializeState
      };
      setup(NodeType::RunDummy, interface);
    }

    void initialize() {
      setupPriority();
      setupConcurrent();
      setupLoop();
      setupFailDummy();
      setupRunDummy();
    }
  }
}
