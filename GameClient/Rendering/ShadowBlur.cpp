#include "Rendering/FullscreenQuad.h"
#include "Rendering/CommandStream.h"
#include "SysGFX/SysGFX.h"
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

    static void draw(CommandStream &stream, SysGFX::RenderTargetHandle renderTarget, const float *offset, SysGFX::TextureHandle texture) {
      stream.writeRenderTargetSet(renderTarget);
      stream.writeUniformVec2Set(Uniforms::list.shadowBlurOffset, 1, offset);
      stream.writeTextureSet(texture);

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, SysGFX::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }

    void initialize() {
      SysGFX::setUniformInt(Uniforms::list.shadowBlurSourceTexture, sourceTextureUnit);
    }

    void write(CommandStream &stream) {
      stream.writeProgramSet(Programs::handles.shadowBlur);
      stream.writeTextureUnitSet(sourceTextureUnit);

      draw(
        stream,
        RenderTargets::handles.shadowBlurHorizontal,
        horizontalOffset,
        Textures::list.shadowVarianceDepth
      );

      draw(
        stream,
        RenderTargets::handles.shadowBlurVertical,
        verticalOffset,
        Textures::list.shadowBlurVarianceDepth
      );
    }
  }
}
