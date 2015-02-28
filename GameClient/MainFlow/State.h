#ifndef MAIN_FLOW_STATE
#define MAIN_FLOW_STATE

#include "Keyboard.h"

namespace MainFlow {
  class State {
  public:
    virtual void enter() { }
    virtual void update(double deltaTime, const Keyboard &keyboard) = 0;
    virtual void exit() { }
    virtual State* checkTransition() = 0;
    virtual ~State() { }
  };
}

#endif
