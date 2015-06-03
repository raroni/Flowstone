#include <assert.h>
#include "Watson/Node.h"

namespace Watson {
  namespace Node {
    const static uint8_t interfaceMax = 32;
    NodeInterface interfaces[interfaceMax] = { { 0 } };

    void setupInterface(uint8_t type, NodeInterface interface) {
      assert(type < interfaceMax);
      interfaces[type] = interface;
    }

    const NodeInterface* getInterface(const void *structure) {
      uint8_t type = *static_cast<const uint8_t*>(structure);
      return &interfaces[type];
    }

    void enter(TraversalFlow *flow) {
      const NodeInterface *interface = getInterface(flow->structure);
      interface->enter(flow);
    }

    void react(TraversalFlow *flow) {
      const NodeInterface *interface = getInterface(flow->structure);
      interface->react(flow);
    }

    void reset(ResetFlow *flow) {
      const NodeInterface *interface = getInterface(flow->structure);
      interface->reset(flow);
    }

    void initializeState(const void *structure, void *state) {
      const NodeInterface *interface = getInterface(structure);
      interface->initializeState(structure, state);
    }
  }
}
