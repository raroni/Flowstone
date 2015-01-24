#include "Rendering/FullscreenQuad.h"
#include "Rendering/CommandStream.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Textures.h"
#include "Rendering/Config.h"
#include "Rendering/RenderTargets.h"
#include "Rendering/Programs.h"
#include "Rendering/ShadowBlur.h"

namespace Rendering {
  namespace ShadowBlur {
    const float horizontalOffset[] = { 1.0/Config::shadowMapSize, 0.0 };
    const float verticalOffset[] = { 0.0, 1.0/Config::shadowMapSize };
    const uint8_t sourceTextureUnit = 0;

    static void draw(CommandStream &stream) {
      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, Backend::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }

    void initialize() {
      Backend::setUniformInt(Uniforms::list.shadowBlurSourceTexture, sourceTextureUnit);
    }

    void write(CommandStream &stream) {
      stream.writeProgramSet(Programs::handles.shadowBlur);
      stream.writeTextureUnitSet(sourceTextureUnit);

      stream.writeRenderTargetSet(RenderTargets::handles.shadowBlurHorizontal);
      stream.writeUniformVec2Set(Uniforms::list.shadowBlurOffset, 1, horizontalOffset);
      stream.writeTextureSet(Textures::list.shadowVarianceDepth);
      draw(stream);

      stream.writeRenderTargetSet(RenderTargets::handles.shadowBlurVertical);
      stream.writeUniformVec2Set(Uniforms::list.shadowBlurOffset, 1, verticalOffset);
      stream.writeTextureSet(Textures::list.shadowBlurVarianceDepth);
      draw(stream);
    }
  }
}
