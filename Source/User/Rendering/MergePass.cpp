#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include "Rendering/Config.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/CommandStream.h"
#include "Rendering/ProgramName.h"
#include "Rendering/Programs.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Textures.h"
#include "Rendering/FullscreenQuad.h"
#include "Rendering/MergePass.h"

namespace Rendering {
  namespace MergePass {
    Quanta::Vector3 primaryLightColor(1, 1, 1);

    void uploadNoiseKernel() {
      uint8_t size = Config::SSAO::noiseSize;
      uint8_t count = pow(size, 2);
      Quanta::Vector3 kernel[count];
      for(uint8_t i=0; count>i; i++) {
        kernel[i] = {
          rand()*2.0f-1,
          rand()*2.0f-1,
          0
        }; // todo: make deterministic instance based (so not affected by any outside changes to srand())
        kernel[i].normalize();
      }
      Backend::setTexture(Textures::list.mergeNoise);
      Backend::writeTexture(size, size, Backend::TextureFormat::SignedNormalizedRGB, kernel);
      Backend::setTexture(0);
    }

    void initialize() {
      uploadNoiseKernel();
    }

    void write(
      CommandStream &stream,
      const Quanta::Matrix4 &cameraClipWorldTransform,
      const Quanta::Matrix4 &lightWorldClipTransform,
      const Quanta::Vector3 &primaryLightDirection,
      const Quanta::Vector3 &secondaryLightDirection
    ) {
      stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::Merge)]);

      stream.writeUniformMat4Set(Uniforms::list.mergeCameraClipWorldTransform, 1, cameraClipWorldTransform.getInverted().components);
      stream.writeUniformMat4Set(Uniforms::list.mergeLightWorldClipTransform, 1, lightWorldClipTransform.components);
      stream.writeUniformVec3Set(Uniforms::list.mergeInversePrimaryLightDirection, 1, primaryLightDirection.getNegated().components);
      stream.writeUniformVec3Set(Uniforms::list.mergePrimaryLightColor, 1, primaryLightColor.components);
      stream.writeUniformVec3Set(Uniforms::list.mergeInverseSecondaryLightDirection, 1, secondaryLightDirection.getNegated().components);

      stream.writeTextureSet(
        Uniforms::list.mergeDiffuse,
        Textures::list.geometryDiffuse,
        0
      );
      stream.writeTextureSet(
        Uniforms::list.mergeNormal,
        Textures::list.geometryNormal,
        1
      );
      stream.writeTextureSet(
        Uniforms::list.mergeDepth,
        Textures::list.geometryDepth,
        2
      );
      stream.writeTextureSet(
        Uniforms::list.mergeShadow,
        Textures::list.shadow,
        3
      );
      stream.writeTextureSet(
        Uniforms::list.mergeNoise,
        Textures::list.mergeNoise,
        4
      );

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, Backend::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
