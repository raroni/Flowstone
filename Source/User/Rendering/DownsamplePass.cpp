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
#include "Rendering/ProgramName.h"
#include "Rendering/DownsamplePass.h"

namespace Rendering {
  namespace DownsamplePass {
    void initialize() {
      Backend::setProgram(Programs::handles[static_cast<size_t>(ProgramName::Downsample)]);
      Backend::setUniformFloat(Uniforms::list.downsampleZNear, 1, &Config::perspective.near);
      Backend::setUniformFloat(Uniforms::list.downsampleZFar, 1, &Config::perspective.far);
      Backend::setProgram(0);
    }

    void write(CommandStream &stream) {
      stream.writeRenderTargetSet(RenderTargets::handles.downsample);
      stream.writeClear(static_cast<Backend::ClearBitMask>(Backend::ClearBit::Color));
      stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::Downsample)]);

      stream.writeTextureSet(Uniforms::list.downsampleDepthTexture, Textures::list.geometryDepth, 0);
      stream.writeTextureSet(Uniforms::list.downsampleNormalTexture, Textures::list.geometryNormal, 1);

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, Backend::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
