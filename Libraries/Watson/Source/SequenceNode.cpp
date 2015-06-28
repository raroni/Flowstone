#include "Misc/Error.h"
#include "Watson/SequenceNode.h"
#include "Watson/NodeType.h"

namespace Watson {
  namespace SequenceNode {
    struct StructureHeader {
      NodeType type;
      uint8_t childCount;
    };

    struct State {
      uint8_t currentChildSlot;
    };

    NodeIndex* getChildren(void *structure) {
      char *structureBytes = static_cast<char*>(structure);
      NodeIndex *children = reinterpret_cast<NodeIndex*>(structureBytes + sizeof(StructureHeader));
      return children;
    }

    const NodeIndex* getChildren(const void *structure) {
      return getChildren(const_cast<void*>(structure));
    }

    void enter(TraversalFlow *flow) {
      State *state = reinterpret_cast<State*>(flow->state);
      const NodeIndex *children = getChildren(flow->structure);
      flow->requestEntry(children[state->currentChildSlot]);
    }

    void react(TraversalFlow *flow) {
      const StructureHeader *header = reinterpret_cast<const StructureHeader*>(flow->structure);
      State *state = reinterpret_cast<State*>(flow->state);

      switch(flow->lastResult) {
        case NodeResult::Failed: {
          state->currentChildSlot = 0;
          flow->requestReaction(NodeResult::Failed);
          break;
        }
        case NodeResult::Running: {
          flow->requestReaction(NodeResult::Running);
          break;
        }
        case NodeResult::Succeeded: {
          state->currentChildSlot++;
          if(state->currentChildSlot == header->childCount) {
            state->currentChildSlot = 0;
            flow->requestReaction(NodeResult::Succeeded);
          } else {
            const NodeIndex *children = getChildren(flow->structure);
            flow->requestEntry(children[state->currentChildSlot]);
          }
          break;
        }
        default: {
          fatalError("Unknown node result.");
        }
      }
    }

    void reset(ResetFlow *flow) {
      State *state = reinterpret_cast<State*>(flow->state);
      state->currentChildSlot = 0;
    }

    void initializeState(const void *structure, void *rawState) {
      State *state = reinterpret_cast<State*>(rawState);
      state->currentChildSlot = 0;
    }

    void writeStructure(void *structure, uint8_t childCount) {
      StructureHeader *header = reinterpret_cast<StructureHeader*>(structure);
      header->childCount = childCount;
    }

    void setChild(void *structure, uint8_t childSlot, NodeIndex childIndex) {
      NodeIndex *children = getChildren(structure);
      children[childSlot] = childIndex;
    }

    uint8_t calcStructureLength(uint8_t childCount) {
      return sizeof(StructureHeader) + sizeof(NodeIndex)*childCount;
    }

    uint8_t calcStateLength(uint8_t childCount) {
      return sizeof(State);
    }
  }
}
