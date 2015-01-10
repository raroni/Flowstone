#include <stddef.h>
#include "Rendering/Config.h"
#include "Rendering/CommandStream.h"
#include "Rendering/RenderTargets.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Textures.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/Programs.h"
#include "Rendering/Backend/ClearBit.h"
#include "Rendering/FullscreenQuad.h"
#include "Rendering/SSAOBlurPass.h"

namespace Rendering {
  namespace SSAOBlurPass {
    namespace TextureUnits {
      uint8_t grain = 0;
      uint8_t depth = 1;
    }

    void initialize() {
      Backend::setProgram(Programs::handles.ssaoBlur);
      Backend::setUniformFloat(Uniforms::list.ssaoBlurDepthDifferenceLimit, 1, &Config::SSAO::blurDepthDifferenceLimit);
      Backend::setUniformFloat(Uniforms::list.ssaoBlurZNear, 1, &Config::perspective.near);
      Backend::setUniformFloat(Uniforms::list.ssaoBlurZFar, 1, &Config::perspective.far);
      Backend::setUniformInt(Uniforms::list.ssaoBlurGrainTexture, TextureUnits::grain);
      Backend::setUniformInt(Uniforms::list.ssaoBlurDepthTexture, TextureUnits::depth);
      Backend::setProgram(0);
    }

    void handleResolutionChange(Resolution resolution) {
      Backend::setProgram(Programs::handles.ssaoBlur);
      float downSampling = static_cast<float>(Config::SSAO::downSampling);
      float grainTexelSize[] = {
        downSampling/resolution.width,
        downSampling/resolution.height
      };
      Backend::setUniformVec2(Uniforms::list.ssaoBlurGrainTexelSize, 1, grainTexelSize);
      Backend::setProgram(0);
    }

    void write(CommandStream &stream) {
      stream.writeRenderTargetSet(RenderTargets::handles.ssaoBlur);
      stream.writeClear(static_cast<Backend::ClearBitMask>(Backend::ClearBit::Color));
      stream.writeProgramSet(Programs::handles.ssaoBlur);

      stream.writeTexturePairSet(TextureUnits::grain, Textures::list.ssaoGrainResult);
      stream.writeTexturePairSet(TextureUnits::depth, Textures::list.downsampleDepth);

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, Backend::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
