#ifndef MAINFLOW_STATE
#define MAINFLOW_STATE

namespace MainFlow {
  class Manager;

  class State {
  protected:
    Manager &manager;
  public:
    State(Manager &manager) : manager(manager) { }
    virtual void enter() { }
    virtual void update(float deltaTime) = 0;
    virtual void exit() { }
    virtual ~State() { }
  };
}

#endif
