#include <stddef.h>
#include "Rendering/CommandStream.h"
#include "Rendering/RenderTargets.h"
#include "Rendering/Textures.h"
#include "Rendering/Config.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Programs.h"
#include "SysGFX/SysGFX.h"
#include "Rendering/FullscreenQuad.h"
#include "SysGFX/ClearBit.h"
#include "Rendering/DownsamplePass.h"

namespace Rendering {
  namespace DownsamplePass {
    namespace TextureUnits {
      const uint8_t depth = 0;
      const uint8_t normal = 1;
    }

    void initialize() {
      SysGFX::setProgram(Programs::handles.downsample);
      SysGFX::setUniformFloat(Uniforms::list.downsampleZNear, 1, &Config::perspective.near);
      SysGFX::setUniformFloat(Uniforms::list.downsampleZFar, 1, &Config::perspective.far);
      SysGFX::setUniformInt(Uniforms::list.downsampleDepthTexture, TextureUnits::depth);
      SysGFX::setUniformInt(Uniforms::list.downsampleNormalTexture, TextureUnits::normal);
      SysGFX::setProgram(0);
    }

    void write(CommandStream &stream) {
      stream.writeRenderTargetSet(RenderTargets::handles.downsample);
      stream.writeClear(static_cast<SysGFX::ClearBitMask>(SysGFX::ClearBit::Color));
      stream.writeProgramSet(Programs::handles.downsample);

      stream.writeTexturePairSet(TextureUnits::depth, Textures::list.geometryDepth);
      stream.writeTexturePairSet(TextureUnits::normal, Textures::list.geometryNormal);

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, SysGFX::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
