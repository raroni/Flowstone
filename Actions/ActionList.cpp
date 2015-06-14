#include <assert.h>
#include "Actions/ActionList.h"

namespace Actions {
  void ActionList::add(ActionTypeIndex type, ActionStateHandle state) {
    assert(max != count);
    types[count] = type;
    states[count] = state;
    count++;
  }

  void ActionList::remove(uint16_t index) {
    count--;
    types[index] = types[count];
    states[index] = states[count];
  }

  uint16_t ActionList::getCount() const {
    return count;
  }

  ActionTypeIndex ActionList::getType(uint16_t index) const {
    return types[index];
  }

  ActionStateHandle ActionList::getState(uint16_t index) const {
    return states[index];
  }
}
