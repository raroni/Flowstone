#include <stdint.h>
#include "Watson/Node.h"
#include "Watson/TraversalFunction.h"
#include "Watson/NodeInterface.h"
#include "Behavior/ThreatCheckNode.h"
#include "Behavior/WoodCheckNode.h"
#include "Behavior/NodeType.h"
#include "Behavior/NodeTypes.h"

namespace Behavior {
  namespace NodeTypes {
    void setupInterface(NodeType type, Watson::NodeInterface interface) {
      Watson::Node::setupInterface(static_cast<uint8_t>(type), interface);
    }

    void setupThreatCheck() {
      Watson::NodeInterface interface = {
        .enter = ThreatCheckNode::enter,
        .reset = ThreatCheckNode::reset,
        .initializeState = ThreatCheckNode::initializeState
      };
      interface.callbacks[ThreatCheckNode::ResponseCallbackIndex] = ThreatCheckNode::handleResponse;
      setupInterface(NodeType::ThreatCheck, interface);
    }

    void setupWoodCheck() {
      Watson::NodeInterface interface = {
        .enter = WoodCheckNode::enter,
        .reset = WoodCheckNode::reset,
        .initializeState = WoodCheckNode::initializeState
      };
      interface.callbacks[WoodCheckNode::ResponseCallbackIndex] = WoodCheckNode::handleResponse;
      setupInterface(NodeType::WoodCheck, interface);
    }

    void setup() {
      setupThreatCheck();
      setupWoodCheck();
    }
  }
}
