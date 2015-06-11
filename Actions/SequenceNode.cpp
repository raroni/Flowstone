#include "Actions/NodeIndex.h"
#include "Actions/SequenceNode.h"

namespace Actions {
  namespace SequenceNode {
    struct State {
      uint8_t currentChildSlot;
    };

    uint8_t stateLength = sizeof(State);

    struct Config {
      uint8_t childCount;
    };

    uint8_t calcConfigLength(uint8_t childCount) {
      return sizeof(Config) + sizeof(NodeIndex)*childCount;
    }

    void writeConfig(void *rawConfig, uint8_t childCount) {
      Config *config = reinterpret_cast<Config*>(rawConfig);
      config->childCount = childCount;
    }

    void start(const void *config, void *state) {

    }
  }
}
