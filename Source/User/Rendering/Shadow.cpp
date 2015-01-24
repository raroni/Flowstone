#include "Rendering/ShadowBasePass.h"
#include "Rendering/Shadow.h"

namespace Rendering {
  namespace Shadow {
    void write(
      CommandStream &stream,
      const BoneMeshRegistry &boneMeshRegistry,
      const DrawSet &drawSet,
      const Quanta::Matrix4 &lightWorldViewTransform,
      const Quanta::Matrix4 &lightViewClipTransform
    ) {
      ShadowBasePass::write(stream, boneMeshRegistry, drawSet, lightWorldViewTransform, lightViewClipTransform);
      // ShadowBlur::write();
    }
  }
}
