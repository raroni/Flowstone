#ifndef RENDERING_CONFIG_H
#define RENDERING_CONFIG_H

#include <stdint.h>
#include <math.h>

namespace Rendering {
  namespace Config {
    const uint8_t maxBoneMeshes = 64;
    const uint16_t maxBoneMeshInstances = 512;
    const uint8_t maxStaticMeshes = 64;
    const uint16_t maxStaticMeshInstances = 512;
    const uint16_t shadowMapSize = 512;
    const uint8_t maxCulledBoneInstances = 128;
    const uint8_t maxCulledStaticInstances = 64;
    const uint8_t cullGroupsCount = 2;

    namespace DrawSet {
      const uint16_t boneCount = 128;
      const uint16_t staticCount = 128;
    }

    struct {
      const float near = 12;
      const float far = 22;
      const float fieldOfView = M_PI/3.0f;
    } perspective;
  }
}

#endif
