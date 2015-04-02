#include "Rendering/CullGroupIndex.h"
#include "Quanta/Math/Matrix4.h"
#include "Rendering/DrawSet.h"
#include "Rendering/BoneMeshInstances.h"
#include "Rendering/StaticMeshInstances.h"
#include "Rendering/PointLights.h"
#include "Rendering/Culler.h"

namespace Rendering {
  namespace CullGroupNames {
    static const CullGroupIndex Bone = 0;
    static const CullGroupIndex Static = 1;
    static const CullGroupIndex PointLight = 2;
  }

  static bool check(const Quanta::Frustum &frustum, const Quanta::Vector3 &position, float boundingRadii) {
    for(uint8_t i=0; 6>i; i++) {
      if(frustum.planes[i].calcDistance(position) + boundingRadii < 0) {
        return false;
      }
    }
    return true;
  }

  void Culler::cullGroupByTransform(
    const Quanta::Frustum &frustum,
    const Quanta::Matrix4 *transforms,
    const float *boundingRadii,
    uint16_t count,
    CullGroupIndex group
  ) {
    uint16_t rangeStart = result.count;
    for(uint16_t i=0; count>i; i++) {
      const float *components = transforms[i].components;
      Quanta::Vector3 position(components[12], components[13], components[14]);
      if(check(frustum, position, boundingRadii[i])) {
        result.addIndex(i);
      }
    }
    result.storeRange(group, rangeStart, result.count);
  }

  void Culler::cullGroupByPosition(
    const Quanta::Frustum &frustum,
    const Quanta::Vector3 *positions,
    const float *boundingRadii,
    uint16_t count,
    CullGroupIndex group
  ) {
    uint16_t rangeStart = result.count;
    for(uint16_t i=0; count>i; i++) {
      if(check(frustum, positions[i], boundingRadii[i])) {
        result.addIndex(i);
      }
    }
    result.storeRange(group, rangeStart, result.count);
  }

  void Culler::fillCullResult(const Quanta::Frustum &frustum) {
    cullGroupByTransform(
      frustum,
      BoneMeshInstances::transforms,
      BoneMeshInstances::boundingRadii,
      BoneMeshInstances::getCount(),
      CullGroupNames::Bone
    );

    cullGroupByTransform(
      frustum,
      StaticMeshInstances::transforms,
      StaticMeshInstances::boundingRadii,
      StaticMeshInstances::getCount(),
      CullGroupNames::Static
    );

    cullGroupByPosition(
      frustum,
      PointLights::positions,
      PointLights::radii,
      PointLights::getCount(),
      CullGroupNames::PointLight
    );
  }

  void Culler::fillDrawSet(DrawSet &drawSet) const {
    CullResultRange range = result.getRange(CullGroupNames::Bone);
    for(uint16_t i=range.start; range.end>i; i++) {
      uint16_t index = result.indices[i];
      drawSet.boneSet.add(
        BoneMeshInstances::transforms[index],
        BoneMeshInstances::meshes[index],
        BoneMeshInstances::poses[index]
      );
    }

    range = result.getRange(CullGroupNames::Static);
    for(uint16_t i=range.start; range.end>i; i++) {
      uint16_t index = result.indices[i];
      drawSet.staticSet.add(
        StaticMeshInstances::transforms[index],
        StaticMeshInstances::meshes[index]
      );
    }

    range = result.getRange(CullGroupNames::PointLight);
    for(uint16_t i=range.start; range.end>i; i++) {
      uint16_t index = result.indices[i];
      drawSet.pointLightSet.add(
        PointLights::positions[index],
        PointLights::radii[index]
      );
    }
  }

  void Culler::cull(const Quanta::Frustum &frustum, DrawSet &drawSet) {
    fillCullResult(frustum);
    fillDrawSet(drawSet);
    result.clear();
  }
}
