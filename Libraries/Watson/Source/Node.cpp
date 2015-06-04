#include <assert.h>
#include "Watson/Node.h"

namespace Watson {
  namespace Node {
    const static uint8_t typeMax = 32;
    NodeInterface interfaces[typeMax] = { { NULL } };

    void setupInterface(uint8_t type, NodeInterface interface) {
      assert(type < typeMax);
      interfaces[type] = interface;
    }

    const NodeInterface* getInterface(const void *structure) {
      uint8_t type = *static_cast<const uint8_t*>(structure);
      return &interfaces[type];
    }

    void enter(TraversalFlow *flow) {
      const NodeInterface *interface = getInterface(flow->structure);
      assert(interface->enter != NULL);
      interface->enter(flow);
    }

    void react(TraversalFlow *flow) {
      const NodeInterface *interface = getInterface(flow->structure);
      assert(interface->react != NULL);
      interface->react(flow);
    }

    void reset(ResetFlow *flow) {
      const NodeInterface *interface = getInterface(flow->structure);
      assert(interface->reset != NULL);
      interface->reset(flow);
    }

    void callback(TraversalFlow *flow, uint8_t index) {
      const NodeInterface *interface = getInterface(flow->structure);
      interface->callbacks[index](flow);
    }

    void initializeState(const void *structure, void *state) {
      const NodeInterface *interface = getInterface(structure);
      interface->initializeState(structure, state);
    }
  }
}
