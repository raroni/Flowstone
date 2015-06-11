#include <assert.h>
#include "Actions/Config.h"
#include "Actions/Node.h"

namespace Actions {
  namespace Node {
    NodeInterface interfaces[static_cast<uint8_t>(NodeTypeIndex::Count)];

    void setup(NodeTypeIndex index, const NodeInterface *interface) {
      interfaces[static_cast<uint8_t>(index)] = *interface;
    }
  }
}
