#include <stddef.h>
#include "Rendering/CommandStream.h"
#include "Rendering/ProgramName.h"
#include "Rendering/Programs.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Textures.h"
#include "Rendering/FullscreenQuad.h"
#include "Rendering/MergePass.h"

namespace Rendering {
  namespace MergePass {
    Quanta::Vector3 atmosphereColor(1, 1, 1);

    void write(
      CommandStream &stream,
      Quanta::Matrix4 geometryClipWorldTransform,
      Quanta::Matrix4 lightWorldClipTransform,
      const Quanta::Vector3 &lightDirection
    ) {
      stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::Merge)]);

      geometryClipWorldTransform.invert();

      stream.writeUniformMat4Set(Uniforms::list.mergeGeometryClipWorldTransform, 1, geometryClipWorldTransform.components);
      stream.writeUniformMat4Set(Uniforms::list.mergeLightWorldClipTransform, 1, lightWorldClipTransform.components);
      stream.writeUniformVec3Set(Uniforms::list.mergeLightDirection, 1, lightDirection.components);
      stream.writeUniformVec3Set(Uniforms::list.mergeAtmosphereColor, 1, atmosphereColor.components);

      stream.writeTextureSet(
        Uniforms::list.mergeDiffuse,
        Textures::list.geometryDiffuse,
        0
      );
      stream.writeTextureSet(
        Uniforms::list.mergeLambert,
        Textures::list.geometryLambert,
        1
      );
      stream.writeTextureSet(
        Uniforms::list.mergeNormal,
        Textures::list.geometryNormal,
        2
      );
      stream.writeTextureSet(
        Uniforms::list.mergeDepth,
        Textures::list.geometryDepth,
        3
      );
      stream.writeTextureSet(
        Uniforms::list.mergeShadow,
        Textures::list.shadow,
        4
      );

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, Backend::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
