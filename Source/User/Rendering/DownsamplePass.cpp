#include <stddef.h>
#include "Rendering/CommandStream.h"
#include "Rendering/RenderTargets.h"
#include "Rendering/Textures.h"
#include "Rendering/Config.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Programs.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/FullscreenQuad.h"
#include "Rendering/Backend/ClearBit.h"
#include "Rendering/DownsamplePass.h"

namespace Rendering {
  namespace DownsamplePass {
    namespace TextureUnits {
      uint8_t depth = 0;
      uint8_t normal = 1;
    }

    void initialize() {
      Backend::setProgram(Programs::handles.downsample);
      Backend::setUniformFloat(Uniforms::list.downsampleZNear, 1, &Config::perspective.near);
      Backend::setUniformFloat(Uniforms::list.downsampleZFar, 1, &Config::perspective.far);
      Backend::setUniformInt(Uniforms::list.downsampleDepthTexture, TextureUnits::depth);
      Backend::setUniformInt(Uniforms::list.downsampleNormalTexture, TextureUnits::normal);
      Backend::setProgram(0);
    }

    void write(CommandStream &stream) {
      stream.writeRenderTargetSet(RenderTargets::handles.downsample);
      stream.writeClear(static_cast<Backend::ClearBitMask>(Backend::ClearBit::Color));
      stream.writeProgramSet(Programs::handles.downsample);

      stream.writeTexturePairSet(TextureUnits::depth, Textures::list.geometryDepth);
      stream.writeTexturePairSet(TextureUnits::normal, Textures::list.geometryNormal);

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, Backend::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
