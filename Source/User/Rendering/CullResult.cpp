#include <assert.h>
#include "Rendering/CullResult.h"

namespace Rendering {
  void CullResult::addBoneInstance(BoneMeshInstanceIndex meshInstance) {
    assert(boneInstances.count != Config::maxCulledBoneInstances);
    boneInstances.list[boneInstances.count++] = meshInstance;
  }

  void CullResult::addStaticInstance(StaticMeshInstanceIndex meshInstance) {
    assert(staticInstances.count != Config::maxCulledStaticInstances);
    staticInstances.list[staticInstances.count++] = meshInstance;
  }

  void CullResult::clear() {
    staticInstances.count = 0;
    boneInstances.count = 0;
  }
}
