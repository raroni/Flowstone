#ifndef RENDERING_CONFIG_H
#define RENDERING_CONFIG_H

#include <stdint.h>
#include <math.h>

namespace Rendering {
  namespace Config {
    const uint8_t maxBoneMeshes = 64;
    const uint16_t maxBoneMeshDraws = 512;
    const uint8_t maxStaticMeshes = 64;
    const uint16_t maxStaticMeshDraws = 512;
    const uint16_t shadowMapSize = 512;
    const uint8_t cullGroupsCount = 3;
    const uint8_t maxPointLights = 32;

    namespace DrawSet {
      const uint16_t boneCount = 128;
      const uint16_t staticCount = 128;
      const uint16_t pointLightCount = 128;
    }

    namespace SSAO {
      const uint8_t noiseSize = 4;
      const uint8_t sampleSize = 16; // also hardcoded in SSAO fragment shader
      const float sampleRadius = 0.4f;
      const float sampleDifferenceLimit = 0.8f;
      const uint8_t downSampling = 2;
      const float blurDepthDifferenceLimit = 0.1;
    }

    namespace Merge {
      const float ssaoDepthDifferenceLimit = 0.01;
    }

    struct {
      const float near = 4.5;
      const float far = 14.0;
      const float fieldOfView = M_PI/3.0f;
    } perspective;
  }
}

#endif
