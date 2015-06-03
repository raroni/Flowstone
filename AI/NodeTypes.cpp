#include <stdint.h>
#include "Watson/Node.h"
#include "Watson/NodeInterface.h"
#include "AI/ThreatCheckNode.h"
#include "AI/NodeType.h"
#include "AI/NodeTypes.h"

namespace AI {
  namespace NodeTypes {
    void setupInterface(NodeType type, Watson::NodeInterface interface) {
      Watson::Node::setupInterface(static_cast<uint8_t>(type), interface);
    }

    void setup() {
      Watson::NodeInterface attackInterface = {
        .enter = ThreatCheckNode::enter,
        .reset = ThreatCheckNode::reset,
        .initializeState = ThreatCheckNode::initializeState
      };
      setupInterface(NodeType::ThreatCheck, attackInterface);
    }
  }
}
