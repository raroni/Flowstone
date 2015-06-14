#ifndef ACTIONS_ACTION_LIST_H
#define ACTIONS_ACTION_LIST_H

#include "Actions/ActionTypeIndex.h"
#include "Actions/ActionStateHandle.h"

namespace Actions {
  class ActionList {
  public:
    void add(ActionTypeIndex type, ActionStateHandle state);
    void remove(uint16_t index);
    uint16_t getCount() const;
    ActionTypeIndex getType(uint16_t index) const;
    ActionStateHandle getState(uint16_t index) const;
  private:
    uint16_t count = 0;
    static const uint16_t max = 256;
    ActionTypeIndex types[max];
    ActionStateHandle states[max];
  };
};

#endif
