#include "Watson/NodeType.h"
#include "Watson/LoopNode.h"

namespace Watson {
  namespace LoopNode {
    struct Structure {
      NodeType type;
      NodeIndex child;
    };

    uint8_t structureLength = sizeof(Structure);
    uint8_t stateLength = 0;

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
