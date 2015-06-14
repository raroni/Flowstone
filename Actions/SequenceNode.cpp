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

    const NodeIndex* getChildren(const void *rawConfig) {
      const char *byteConfig = static_cast<const char*>(rawConfig);
      return reinterpret_cast<const NodeIndex*>(byteConfig+sizeof(ConfigHeader));
    }

    NodeIndex* getChildren(void *mutableConfig) {
      const void* constConfig = static_cast<const void*>(mutableConfig);
      const NodeIndex *children = getChildren(constConfig);
      return const_cast<NodeIndex*>(children);
    }

    void configure(const void *rawArgs, void *rawConfig) {
      const ConfigArgSet *args = reinterpret_cast<const ConfigArgSet*>(rawArgs);
      ConfigHeader *header = reinterpret_cast<ConfigHeader*>(rawConfig);
      header->childCount = args->childCount;
      NodeIndex *children = getChildren(rawConfig);
      for(uint8_t i=0; i<args->childCount; ++i) {
        children[i] = args->children[i];
      }
    }

    bool isCompleted(NodeFlow *flow) {
      return false;
    }

    void start(NodeFlow *flow) {
      const NodeIndex *children = getChildren(flow->getConfig());
      flow->start(children[0]);
    }
  }
}
