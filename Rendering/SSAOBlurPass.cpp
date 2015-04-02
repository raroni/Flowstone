#include <stddef.h>
#include "Rendering/Config.h"
#include "Rendering/CommandStream.h"
#include "Rendering/RenderTargets.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Textures.h"
#include "SysGFX/SysGFX.h"
#include "Rendering/Programs.h"
#include "SysGFX/ClearBit.h"
#include "Rendering/FullscreenQuad.h"
#include "Rendering/SSAOBlurPass.h"

namespace Rendering {
  namespace SSAOBlurPass {
    namespace TextureUnits {
      const uint8_t grain = 0;
      const uint8_t depth = 1;
    }

    void initialize() {
      SysGFX::setProgram(Programs::handles.ssaoBlur);
      SysGFX::setUniformFloat(Uniforms::list.ssaoBlurDepthDifferenceLimit, 1, &Config::SSAO::blurDepthDifferenceLimit);
      SysGFX::setUniformFloat(Uniforms::list.ssaoBlurZNear, 1, &Config::perspective.near);
      SysGFX::setUniformFloat(Uniforms::list.ssaoBlurZFar, 1, &Config::perspective.far);
      SysGFX::setUniformInt(Uniforms::list.ssaoBlurGrainTexture, TextureUnits::grain);
      SysGFX::setUniformInt(Uniforms::list.ssaoBlurDepthTexture, TextureUnits::depth);
      SysGFX::setProgram(0);
    }

    void handleResolutionChange(Resolution resolution) {
      SysGFX::setProgram(Programs::handles.ssaoBlur);
      float downSampling = static_cast<float>(Config::SSAO::downSampling);
      float grainTexelSize[] = {
        downSampling/resolution.width,
        downSampling/resolution.height
      };
      SysGFX::setUniformVec2(Uniforms::list.ssaoBlurGrainTexelSize, 1, grainTexelSize);
      SysGFX::setProgram(0);
    }

    void write(CommandStream &stream) {
      stream.writeRenderTargetSet(RenderTargets::handles.ssaoBlur);
      stream.writeClear(static_cast<SysGFX::ClearBitMask>(SysGFX::ClearBit::Color));
      stream.writeProgramSet(Programs::handles.ssaoBlur);

      stream.writeTexturePairSet(TextureUnits::grain, Textures::list.ssaoGrainResult);
      stream.writeTexturePairSet(TextureUnits::depth, Textures::list.downsampleDepth);

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, SysGFX::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
