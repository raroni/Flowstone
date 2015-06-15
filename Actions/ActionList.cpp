#include <assert.h>
#include "Actions/ActionList.h"

namespace Actions {
  void ActionList::add(ActionTypeIndex type, ActionStateHandle state, Database::EntityHandle entityHandle) {
    assert(max != count);
    types[count] = type;
    states[count] = state;
    entityHandles[count] = entityHandle;
    count++;
  }

  void ActionList::remove(uint16_t index) {
    count--;
    types[index] = types[count];
    states[index] = states[count];
    entityHandles[index] = entityHandles[count];
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

  Database::EntityHandle ActionList::getEntityHandle(uint16_t index) const {
    return entityHandles[index];
  }
}
