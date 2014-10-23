#ifndef MAINFLOW_STATE
#define MAINFLOW_STATE

namespace MainFlow {
  class State {
  public:
    virtual void enter() { }
    virtual void update(float deltaTime) = 0;
    virtual void exit() { }
    virtual State* checkTransition() = 0;
    virtual ~State() { }
  };
}

#endif
