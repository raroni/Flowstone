#include "Rendering/StaticMeshInstances.h"
#include "Rendering/CullResult.h"
#include "Rendering/Culler.h"

namespace Rendering {
  void Culler::addStatic(StaticMeshInstanceIndex instance, float radius) {
    staticInstances.radii[staticInstances.count] = radius;
    staticInstances.indices[staticInstances.count] = instance;
    staticInstances.count++;
  }

  void Culler::addBone(BoneMeshInstanceIndex instance, float radius) {
    boneInstances.radii[boneInstances.count] = radius;
    boneInstances.indices[boneInstances.count] = instance;
    boneInstances.count++;
  }

  void Culler::cull(const Quanta::Frustum &frustum, CullResult &result) const {
    /*
    for(uint16_t i=0; staticInstances.count>i; i++) {
      StaticMeshInstanceIndex index = staticInstances.indices[i];
      StaticMeshInstance &instance = StaticMeshInstances::list[index];
      if(check(frustum, staticTransforms[instance.transform], staticInstances.radii[i])) {
        result.addStaticInstance(index);
      }
    }
    */
  }

  bool Culler::check(const Quanta::Frustum &frustum, const Quanta::Matrix4 &transform, float radius) const {
    return true;
  }
}
