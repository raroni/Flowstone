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

    void startExecution(ActionType type, Database::EntityHandle entity) {
      ActionInterface *interface = getInterface(type);
      interface->startExecution(entity);
    }
  }
}
