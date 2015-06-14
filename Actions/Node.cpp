#include <assert.h>
#include "Actions/Config.h"
#include "Actions/Node.h"

namespace Actions {
  namespace Node {
    NodeInterface interfaces[static_cast<uint8_t>(NodeTypeIndex::Count)];

    NodeInterface* getInterface(NodeTypeIndex index) {
      uint8_t indexInt = static_cast<uint8_t>(index);
      return &interfaces[indexInt];
    }

    void setup(NodeTypeIndex index, const NodeInterface *interface) {
      interfaces[static_cast<uint8_t>(index)] = *interface;
    }

    uint8_t calcConfigLength(NodeTypeIndex index, const void *args) {
      return getInterface(index)->calcConfigLength(args);
    }

    uint8_t calcStateLength(NodeTypeIndex index, const void *args) {
      return getInterface(index)->calcStateLength(args);
    }

    void start(NodeTypeIndex index, NodeFlow *flow) {
      getInterface(index)->start(flow);
    }

    bool isCompleted(NodeTypeIndex index, NodeFlow *flow) {
      return getInterface(index)->isCompleted(flow);
    }

    void configure(NodeTypeIndex index, const void *args, void *config) {
      getInterface(index)->configure(args, config);
    }
  }
}
