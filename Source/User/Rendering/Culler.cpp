#include "Rendering/StaticMeshInstances.h"
#include "Rendering/CullResult.h"
#include "Rendering/Culler.h"

namespace Rendering {
  void Culler::configureGroup(CullGroupIndex group, const Quanta::Matrix4 *transforms, const float *boundingRadii) {
    groups[group].transforms = transforms;
    groups[group].boundingRadii = boundingRadii;
  }

  static bool check(const Quanta::Frustum &frustum, const Quanta::Vector3 &position, float boundingRadii) {
    for(uint8_t i=0; 6>i; i++) {
      if(frustum.planes[i].calcDistance(position) + boundingRadii < 0) {
        return false;
      }
    }
    return true;
  }

  void Culler::cull(const Quanta::Frustum &frustum, CullResult &result, const uint16_t *counts) {
    for(uint8_t i=0; Config::cullGroupsCount>i; i++) {
      Group &group = groups[i];
      uint16_t rangeStart = result.count;
      for(uint16_t n=0; counts[i]>n; n++) {
        const float *components = group.transforms[n].components;
        Quanta::Vector3 position(components[12], components[13], components[14]);
        if(check(frustum, position, group.boundingRadii[n])) {
          result.addIndex(n);
        }
      }
      result.storeRange(i, rangeStart, result.count);
    }
  }
}
