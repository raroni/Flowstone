#ifndef RENDERING2_OBJECT_ID_CASTER_H
#define RENDERING2_OBJECT_ID_CASTER_H

#include "Rendering2/ObjectID.h"
#include "Rendering2/AnimatedMeshInstanceIndex.h"

namespace Rendering2 {
  namespace ObjectIDCaster {
    ObjectID createByAnimatedMeshInstanceIndex(AnimatedMeshInstanceIndex index);
  }
}

#endif
