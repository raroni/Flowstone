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

    void initialize() {
      Backend::setProgram(Programs::handles[static_cast<size_t>(ProgramName::Merge)]);
      Backend::setUniformFloat(Uniforms::list.mergeZNear, 1, &Config::perspective.near);
      Backend::setUniformFloat(Uniforms::list.mergeZFar, 1, &Config::perspective.far);
      float downSampling = Config::SSAO::downSampling;
      Backend::setUniformFloat(Uniforms::list.mergeDownsampleScale, 1, &downSampling);
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

      stream.writeTextureSet(Uniforms::list.mergeDiffuse, Textures::list.geometryDiffuse, 0);
      stream.writeTextureSet(Uniforms::list.mergeNormal, Textures::list.geometryNormal, 1);
      stream.writeTextureSet(Uniforms::list.mergeDepth, Textures::list.geometryDepth, 2);
      stream.writeTextureSet(Uniforms::list.mergeShadow, Textures::list.shadow, 3);
      stream.writeTextureSet(Uniforms::list.mergeSSAOTexture, Textures::list.ssaoBlur, 4);
      stream.writeTextureSet(Uniforms::list.mergeLowResDepthTexture, Textures::list.downsampleDepth, 5);

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, Backend::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
