#include <assert.h>
#include "Watson/NodeType.h"
#include "Watson/ConcurrentNode.h"

namespace Watson {
  namespace ConcurrentNode {
    struct StructureHeader {
      NodeType type;
      uint8_t childCount;
    };

    struct State {
      uint8_t currentChildSlot;
    };

    NodeIndex* getChildren(void *structure) {
      char* structureBytes = static_cast<char*>(structure);
      NodeIndex *children = reinterpret_cast<NodeIndex*>(structureBytes + sizeof(StructureHeader));
      return children;
    }

    const NodeIndex* getChildren(const void *structure) {
      return getChildren(const_cast<void*>(structure));
    }

    void enter(TraversalFlow *flow) {
      const NodeIndex *children = getChildren(flow->structure);
      flow->requestEntry(children[0]);
    }

    void react(TraversalFlow *flow) {
      NodeResult lastResult = flow->lastResult;
      switch(lastResult) {
        case NodeResult::Failed: {
          flow->requestReaction(NodeResult::Failed);
          break;
        }
        case NodeResult::Succeeded: {
          const StructureHeader *header = reinterpret_cast<const StructureHeader*>(flow->structure);
          State *state = reinterpret_cast<State*>(flow->state);
          state->currentChildSlot++;
          if(state->currentChildSlot == header->childCount) {
            flow->requestReaction(NodeResult::Succeeded);
          } else {
            const NodeIndex *children = getChildren(flow->structure);
            flow->requestEntry(children[state->currentChildSlot]);
          }
          break;
        }
        default: {
          const StructureHeader *header = reinterpret_cast<const StructureHeader*>(flow->structure);
          State *state = reinterpret_cast<State*>(flow->state);
          if(lastResult == NodeResult::Running && state->currentChildSlot == header->childCount-1) {
            flow->requestReaction(NodeResult::Running);
          } else {
            assert(false);
          }
        }
      }
    }

    void reset(ResetFlow *flow) {

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

    uint8_t calcStateLength(uint8_t childCount) {
      return 0;
    }

    uint8_t calcStructureLength(uint8_t childCount) {
      return sizeof(StructureHeader) + sizeof(NodeIndex)*childCount;
    }
  }
}
