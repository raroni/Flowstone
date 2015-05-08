#include <assert.h>
#include "Database/EntityManager.h"

namespace Database {
  EntityManager::EntityManager(EntityHandle *handles, uint16_t max) :
  handles(handles), max(max) { }

  EntityHandle EntityManager::create() {
    assert(max != count);
    EntityHandle handle = count; // quick'n dirty, should use some kind of pool
    handles[count] = handle;
    count++;
    return handle;
  }

  uint16_t EntityManager::getCount() {
    return count;
  }
}
