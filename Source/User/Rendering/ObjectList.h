#ifndef Rendering_OBJECT_LIST_H
#define Rendering_OBJECT_LIST_H

#include "Rendering/Config.h"
#include "Rendering/Object.h"

namespace Rendering {
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
