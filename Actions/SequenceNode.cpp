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
      const CreationArgSet *args = reinterpret_cast<const CreationArgSet*>(rawArgs);
      return sizeof(ConfigHeader) + sizeof(NodeIndex)*args->childCount;
    }

    uint8_t calcStateLength(const void *args) {
      return sizeof(State);
    }

    void writeConfig(void *rawConfig, uint8_t childCount) {
      ConfigHeader *header = reinterpret_cast<ConfigHeader*>(rawConfig);
      header->childCount = childCount;
    }

    void start(const void *config, void *state) {

    }
  }
}
