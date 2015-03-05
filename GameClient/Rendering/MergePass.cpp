#include <stddef.h>
#include "SysGFX/SysGFX.h"
#include "Rendering/Config.h"
#include "Rendering/CommandStream.h"
#include "Rendering/Programs.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Textures.h"
#include "Rendering/FullscreenQuad.h"
#include "Rendering/MergePass.h"

namespace Rendering {
  namespace MergePass {
    Quanta::Vector3 primaryLightColor(1, 1, 1);

    namespace TextureUnits {
      const uint8_t appearance = 0;
      const uint8_t normal = 1;
      const uint8_t depth = 2;
      const uint8_t shadow = 3;
      const uint8_t ssao = 4;
      const uint8_t downsampleDepth = 5;
    }

    void initialize() {
      SysGFX::setProgram(Programs::handles.merge);
      SysGFX::setUniformFloat(Uniforms::list.mergeZNear, 1, &Config::perspective.near);
      SysGFX::setUniformFloat(Uniforms::list.mergeZFar, 1, &Config::perspective.far);
      float inverseShadowSize = 1.0/Config::shadowMapSize;
      SysGFX::setUniformFloat(Uniforms::list.mergeInverseShadowSize, 1, &inverseShadowSize);
      SysGFX::setUniformUInt(Uniforms::list.mergeDownsampleScale, Config::SSAO::downSampling);
      SysGFX::setUniformInt(Uniforms::list.mergeAppearanceTexture, TextureUnits::appearance);
      SysGFX::setUniformInt(Uniforms::list.mergeNormalTexture, TextureUnits::normal);
      SysGFX::setUniformInt(Uniforms::list.mergeDepthTexture, TextureUnits::depth);
      SysGFX::setUniformInt(Uniforms::list.mergeShadowTexture, TextureUnits::shadow);
      SysGFX::setUniformInt(Uniforms::list.mergeSSAOTexture, TextureUnits::ssao);
      SysGFX::setUniformInt(Uniforms::list.mergeLowResDepthTexture, TextureUnits::downsampleDepth);
      SysGFX::setProgram(0);
    }

    void write(
      CommandStream &stream,
      const Quanta::Matrix4 &cameraClipWorldTransform,
      const Quanta::Matrix4 &lightWorldViewTransform,
      const Quanta::Matrix4 &lightViewClipTransform,
      const Quanta::Vector3 &primaryLightDirection,
      const Quanta::Vector3 &secondaryLightDirection
    ) {
      stream.writeProgramSet(Programs::handles.merge);

      stream.writeUniformMat4Set(Uniforms::list.mergeCameraClipWorldTransform, 1, cameraClipWorldTransform.components);
      stream.writeUniformMat4Set(Uniforms::list.mergeLightWorldViewTransform, 1, lightWorldViewTransform.components);
      stream.writeUniformMat4Set(Uniforms::list.mergeLightViewClipTransform, 1, lightViewClipTransform.components);
      stream.writeUniformVec3Set(Uniforms::list.mergeInversePrimaryLightDirection, 1, primaryLightDirection.getNegated().components);
      stream.writeUniformVec3Set(Uniforms::list.mergePrimaryLightColor, 1, primaryLightColor.components);
      stream.writeUniformVec3Set(Uniforms::list.mergeInverseSecondaryLightDirection, 1, secondaryLightDirection.getNegated().components);

      stream.writeTexturePairSet(TextureUnits::appearance, Textures::list.geometryAppearance);
      stream.writeTexturePairSet(TextureUnits::normal, Textures::list.geometryNormal);
      stream.writeTexturePairSet(TextureUnits::depth, Textures::list.geometryDepth);
      stream.writeTexturePairSet(TextureUnits::shadow, Textures::list.shadowVarianceDepth);
      stream.writeTexturePairSet(TextureUnits::ssao, Textures::list.ssaoBlur);
      stream.writeTexturePairSet(TextureUnits::downsampleDepth, Textures::list.downsampleDepth);

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, SysGFX::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
