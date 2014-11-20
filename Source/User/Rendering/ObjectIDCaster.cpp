#include "Rendering/ObjectIDCaster.h"

namespace Rendering {
  namespace ObjectIDCaster {
    union AnimatedMeshInstanceIndexCaster {
      AnimatedMeshInstanceIndex index;
      ObjectID id;
    };

    ObjectID createByAnimatedMeshInstanceIndex(AnimatedMeshInstanceIndex index) {
      AnimatedMeshInstanceIndexCaster caster;
      caster.index = index;
      return caster.id;
    }
  }
}
