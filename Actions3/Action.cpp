#include <assert.h>
#include "Actions3/Action.h"

namespace Actions3 {
  namespace Action {
    const uint8_t max = static_cast<uint8_t>(ActionType::Count);
    ActionInterface interfaces[max];

    uint8_t getTypeInt(ActionType type) {
      return static_cast<uint8_t>(type);
    }

    ActionInterface* getInterface(ActionType type) {
      uint8_t typeInt = getTypeInt(type);
      assert(typeInt < max);
      return &interfaces[typeInt];
    }

    void setup(ActionType type, const ActionInterface *newInterface) {
      ActionInterface *currentInterface = getInterface(type);
      *currentInterface = *newInterface;
    }

    void startExecution(ActionType type, Database::EntityHandle entity, void *state, const void *options) {
      ActionInterface *interface = getInterface(type);
      assert(interface->startExecution != nullptr);
      interface->startExecution(entity, state, options);
    }

    void updateExecution(ActionType type, Database::EntityHandle entity, void *state, const void *options) {
      ActionInterface *interface = getInterface(type);
      assert(interface->updateExecution != nullptr);
      interface->updateExecution(entity, state, options);
    }

    uint8_t getStateLength(ActionType type) {
      ActionInterface *interface = getInterface(type);
      assert(interface->getStateLength != nullptr);
      return interface->getStateLength();
    }

    uint8_t getOptionsLength(ActionType type) {
      ActionInterface *interface = getInterface(type);
      assert(interface->getOptionsLength != nullptr);
      return interface->getOptionsLength();
    }
  }
}
