#ifndef DATABASE_ENTITY_MANAGER_H
#define DATABASE_ENTITY_MANAGER_H

#include "Database/EntityHandle.h"

namespace Database {
  class EntityManager {
  public:
    EntityManager(EntityHandle *handles, uint16_t entityMax);
    EntityHandle *handles;
    EntityHandle create();
    uint16_t getCount();
  private:
    uint16_t count = 0;
    uint16_t max;
  };
}

#endif
