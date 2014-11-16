#ifndef RENDERING2_OBJECT_LIST_H
#define RENDERING2_OBJECT_LIST_H

#include "Rendering2/Config.h"
#include "Rendering2/Object.h"

namespace Rendering2 {
  class ObjectList {
  public:
  private:
    Object objects[Config::maxObjects];
    uint16_t count = 0;
  public:
    ObjectIndex create(ObjectType type, ObjectID id) {
      objects[count] = { type, id };
      return count++;
    }
    const Object* getObjects() const {
      return objects;
    }
    uint16_t getCount() const {
      return count;
    }
  };
}

#endif
