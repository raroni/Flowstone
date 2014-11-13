#ifndef MAIN_FLOW_MANAGER_H
#define MAIN_FLOW_MANAGER_H

#include "Mainflow/PlayState.h"
#include "Mainflow/State.h"

namespace MainFlow {
  class Manager {
    State *state = nullptr;
  public:
    void initialize(Rendering2::Renderer &renderer) {
      State *state = new PlayState(renderer);
      changeState(state);
    }
    void update(double timeDelta) {
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

#endif
