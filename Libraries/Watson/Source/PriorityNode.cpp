#include "Watson/PriorityNode.h"
#include "Watson/NodeType.h"

namespace Watson {
  namespace PriorityNode {
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
      const NodeIndex *children = getChildren(flow->structure);
      flow->requestEntry(children[0]);
    }

    void react(TraversalFlow *flow) {
      const StructureHeader *header = reinterpret_cast<const StructureHeader*>(flow->structure);
      State *state = reinterpret_cast<State*>(flow->state);

      state->currentChildSlot++;
      if(state->currentChildSlot == header->childCount) {
        state->currentChildSlot = 0;
        flow->requestReaction(flow->lastResult);
      } else {
        const NodeIndex *children = getChildren(flow->structure);
        flow->requestEntry(children[state->currentChildSlot]);
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

    uint8_t calcStructureLength(uint8_t childCount) {
      return sizeof(StructureHeader) + sizeof(NodeIndex)*childCount;
    }

    uint8_t calcStateLength(uint8_t childCount) {
      return sizeof(State);
    }
  }
}
