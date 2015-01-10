#include <stddef.h>
#include "Rendering/Backend/Functions.h"
#include "Rendering/Config.h"
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

    namespace TextureUnits {
      uint8_t diffuse = 0;
      uint8_t normal = 1;
      uint8_t depth = 2;
      uint8_t shadow = 3;
      uint8_t ssao = 4;
      uint8_t downsampleDepth = 5;
    }

    void initialize() {
      Backend::setProgram(Programs::handles[static_cast<size_t>(ProgramName::Merge)]);
      Backend::setUniformFloat(Uniforms::list.mergeZNear, 1, &Config::perspective.near);
      Backend::setUniformFloat(Uniforms::list.mergeZFar, 1, &Config::perspective.far);
      Backend::setUniformUInt(Uniforms::list.mergeDownsampleScale, Config::SSAO::downSampling);
      Backend::setUniformInt(Uniforms::list.mergeDiffuseTexture, TextureUnits::diffuse);
      Backend::setUniformInt(Uniforms::list.mergeNormalTexture, TextureUnits::normal);
      Backend::setUniformInt(Uniforms::list.mergeDepthTexture, TextureUnits::depth);
      Backend::setUniformInt(Uniforms::list.mergeShadowTexture, TextureUnits::shadow);
      Backend::setUniformInt(Uniforms::list.mergeSSAOTexture, TextureUnits::ssao);
      Backend::setUniformInt(Uniforms::list.mergeLowResDepthTexture, TextureUnits::downsampleDepth);
      Backend::setProgram(0);
    }

    void write(
      CommandStream &stream,
      const Quanta::Matrix4 &cameraClipWorldTransform,
      const Quanta::Matrix4 &lightWorldClipTransform,
      const Quanta::Vector3 &primaryLightDirection,
      const Quanta::Vector3 &secondaryLightDirection
    ) {
      stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::Merge)]);

      stream.writeUniformMat4Set(Uniforms::list.mergeCameraClipWorldTransform, 1, cameraClipWorldTransform.components);
      stream.writeUniformMat4Set(Uniforms::list.mergeLightWorldClipTransform, 1, lightWorldClipTransform.components);
      stream.writeUniformVec3Set(Uniforms::list.mergeInversePrimaryLightDirection, 1, primaryLightDirection.getNegated().components);
      stream.writeUniformVec3Set(Uniforms::list.mergePrimaryLightColor, 1, primaryLightColor.components);
      stream.writeUniformVec3Set(Uniforms::list.mergeInverseSecondaryLightDirection, 1, secondaryLightDirection.getNegated().components);

      stream.writeTexturePairSet(TextureUnits::diffuse, Textures::list.geometryDiffuse);
      stream.writeTexturePairSet(TextureUnits::normal, Textures::list.geometryNormal);
      stream.writeTexturePairSet(TextureUnits::depth, Textures::list.geometryDepth);
      stream.writeTexturePairSet(TextureUnits::shadow, Textures::list.shadow);
      stream.writeTexturePairSet(TextureUnits::ssao, Textures::list.ssaoBlur);
      stream.writeTexturePairSet(TextureUnits::downsampleDepth, Textures::list.downsampleDepth);

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, Backend::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
