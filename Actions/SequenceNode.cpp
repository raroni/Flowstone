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

    bool isCompleted(NodeCall *call) {
      const NodeIndex *children = ParentNode::getChildren(call->getConfig());
      State *state = reinterpret_cast<State*>(call->getState());
      NodeIndex currentChildIndex = children[state->currentChildSlot];
      if(call->getFlow()->isCompleted(currentChildIndex)) {
        uint8_t childCount = ParentNode::getChildCount(call->getConfig());
        if(childCount-1 == state->currentChildSlot) {
          return true;
        } else {
          state->currentChildSlot++;
          NodeIndex newChildIndex = children[state->currentChildSlot];
          call->getFlow()->start(newChildIndex);
        }
      }
      return false;
    }

    void start(NodeCall *call) {
      const NodeIndex *children = ParentNode::getChildren(call->getConfig());
      call->getFlow()->start(children[0]);
    }
  }
}
