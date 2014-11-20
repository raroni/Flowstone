#ifndef Rendering_OBJECT_ID_CASTER_H
#define Rendering_OBJECT_ID_CASTER_H

#include "Rendering/ObjectID.h"
#include "Rendering/AnimatedMeshInstanceIndex.h"

namespace Rendering {
  namespace ObjectIDCaster {
    ObjectID createByAnimatedMeshInstanceIndex(AnimatedMeshInstanceIndex index);
  }
}

#endif
