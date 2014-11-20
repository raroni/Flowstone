#ifndef Rendering_OBJECT_H
#define Rendering_OBJECT_H

#include "Rendering/ObjectType.h"
#include "Rendering/ObjectID.h"

namespace Rendering {
  struct Object {
    ObjectType type;
    ObjectID id;
  };
}

#endif
