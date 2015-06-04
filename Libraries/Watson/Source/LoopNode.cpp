#include "Watson/LoopNode.h"

namespace Watson {
  namespace LoopNode {
    uint8_t structureLength = 1;
    uint8_t stateLength = 0;

    struct Structure {
      NodeIndex child;
    };

    void requestChildEntry(TraversalFlow *flow) {
      const Structure *structure = reinterpret_cast<const Structure*>(flow->structure);
      flow->requestEntry(structure->child);
    }

    void enter(TraversalFlow *flow) {
      requestChildEntry(flow);
    }

    void react(TraversalFlow *flow) {
      NodeResult result = flow->lastResult;
      if(result == NodeResult::Failed || result == NodeResult::Running) {
        flow->requestReaction(result);
      } else {
        requestChildEntry(flow);
      }
    }

    void reset(ResetFlow *flow) { }

    void initializeState(const void *structure, void *state) { }

    void setChild(void *structureRaw, NodeIndex childIndex) {
      Structure *structure = reinterpret_cast<Structure*>(structureRaw);
      structure->child = childIndex;
    }
  }
}
