#ifndef CLIENT_MAIN_FLOW_STATE
#define CLIENT_MAIN_FLOW_STATE

#include "Client/Keyboard.h"

namespace Client {
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
}

#endif
