#include "Rendering/ObjectIDCaster.h"

namespace Rendering {
  namespace ObjectIDCaster {
    union BoneMeshInstanceIndexCaster {
      BoneMeshInstanceIndex index;
      ObjectID id;
    };

    ObjectID createByBoneMeshInstanceIndex(BoneMeshInstanceIndex index) {
      BoneMeshInstanceIndexCaster caster;
      caster.index = index;
      return caster.id;
    }
  }
}
