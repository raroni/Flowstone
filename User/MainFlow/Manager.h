#include "Mainflow/State.h"

namespace MainFlow {
  class Manager {
    State *currentState = nullptr;
    State *pendingState = nullptr;
  public:
    void changeState(State *state) {
      pendingState = state;
    }
    void update() {
      if(pendingState != nullptr) {
        if(currentState != nullptr) {
          currentState->exit();
          delete currentState;
        }
        currentState = pendingState;
        pendingState = nullptr;
        currentState->enter();
      }
    }
    State* getState() {
      return currentState;
    }
    ~Manager() {
      if(currentState != nullptr) {
        currentState->exit();
        delete currentState;
      }
      delete pendingState;
    }
  };
}
