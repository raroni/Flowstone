#include "Actions/NodeIndex.h"
#include "Actions/SequenceNode.h"

namespace Actions {
  namespace SequenceNode {
    struct State {
      uint8_t currentChildSlot;
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
      const NodeIndex *children = ParentNode::getChildren(flow->getConfig());
      State *state = reinterpret_cast<State*>(flow->getState());
      NodeIndex currentChildIndex = children[state->currentChildSlot];
      if(flow->isCompleted(currentChildIndex)) {
        uint8_t childCount = ParentNode::getChildCount(flow->getConfig());
        if(childCount-1 == state->currentChildSlot) {
          return true;
        } else {
          state->currentChildSlot++;
          NodeIndex newChildIndex = children[state->currentChildSlot];
          flow->start(newChildIndex);
        }
      }
      return false;
    }

    void start(NodeFlow *flow) {
      const NodeIndex *children = ParentNode::getChildren(flow->getConfig());
      flow->start(children[0]);
    }
  }
}
