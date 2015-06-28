#include <assert.h>
#include "Watson/NodeType.h"
#include "Watson/NodeResult.h"
#include "Watson/InverterNode.h"

namespace Watson {
  namespace InverterNode {
    struct Structure {
      NodeType type;
      NodeIndex child;
    };

    uint8_t structureLength = sizeof(Structure);
    uint8_t stateLength = 0;

    void enter(TraversalFlow *flow) {
      const Structure *structure = reinterpret_cast<const Structure*>(flow->structure);
      flow->requestEntry(structure->child);
    }

    void react(TraversalFlow *flow) {
      assert(flow->lastResult == NodeResult::Succeeded || flow->lastResult == NodeResult::Failed);
      if(flow->lastResult == NodeResult::Succeeded) {
        flow->requestReaction(NodeResult::Failed);
      } else {
        flow->requestReaction(NodeResult::Succeeded);
      }
    }

    void setChild(void *structureRaw, NodeIndex childIndex) {
      Structure *structure = reinterpret_cast<Structure*>(structureRaw);
      structure->child = childIndex;
    }

    void reset(ResetFlow *flow) { }
    void initializeState(const void *structure, void *state) { }
  }
}
