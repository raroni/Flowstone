#include "Rendering/SSAOGrainPass.h"
#include "Rendering/SSAOBlurPass.h"
#include "Rendering/DownsamplePass.h"
#include "Rendering/Config.h"
#include "Rendering/CommandStream.h"

namespace Rendering {
  namespace SSAO {
    void initialize() {
      SSAOGrainPass::initialize();
      SSAOBlurPass::initialize();
      DownsamplePass::initialize();
    }

    void handleResolutionChange(Resolution resolution) {
      SSAOGrainPass::handleResolutionChange(resolution);
      SSAOBlurPass::handleResolutionChange(resolution);
    }

    void write(
      CommandStream &stream,
      Resolution resolution,
      const Quanta::Matrix4 &clipWorldTransform
    ) {
      stream.writeViewportSet(resolution.width/Config::SSAO::downSampling, resolution.height/Config::SSAO::downSampling);
      DownsamplePass::write(stream);
      SSAOGrainPass::write(stream, clipWorldTransform);
      SSAOBlurPass::write(stream);
      stream.writeViewportSet(resolution.width, resolution.height);
    }
  }
}
