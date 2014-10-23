#include "Mainflow/SinglePlayerState.h"
#include "Mainflow/State.h"

namespace MainFlow {
  class Manager {
    State *state = nullptr;
  public:
    Manager() {
      state = new SinglePlayerState();
    }
    void update(float timeDelta) {
      State* newState = state->checkTransition();
      if(newState != nullptr) {
        changeState(newState);
      }
      state->update(timeDelta);
    }
    void changeState(State *newState) {
      if(state != nullptr) {
        state->exit();
      }
      state = newState;
      state->enter();
    }
    ~Manager() {
      if(state != nullptr) {
        state->exit();
        delete state;
      }
    }
  };
}
