#include "Rendering2/ObjectIDCaster.h"

namespace Rendering2 {
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
