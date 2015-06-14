#include "Actions/NodeIndex.h"
#include "Actions/SequenceNode.h"

namespace Actions {
  namespace SequenceNode {
    struct State {
      uint8_t currentChildSlot;
    };

    struct ConfigHeader {
      uint8_t childCount;
    };

    uint8_t calcConfigLength(const void *rawArgs) {
      return ParentNode::calcConfigLength(rawArgs);
    }

    uint8_t calcStateLength(const void *args) {
      return sizeof(State);
    }

    void configure(const void *args, void *config) {
      ParentNode::configure(args, config);
    }

    bool isCompleted(NodeFlow *flow) {
      return false;
    }

    void start(NodeFlow *flow) {
      const NodeIndex *children = ParentNode::getChildren(flow->getConfig());
      flow->start(children[0]);
    }
  }
}
