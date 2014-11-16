#ifndef RENDERING2_OBJECT_H
#define RENDERING2_OBJECT_H

#include "Rendering2/ObjectType.h"
#include "Rendering2/ObjectID.h"

namespace Rendering2 {
  struct Object {
    ObjectType type;
    ObjectID id;
  };
}

#endif
