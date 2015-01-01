#include <stdint.h>
#include <stddef.h>
#include "Quanta/Math/Vector3.h"
#include "Quanta/Util.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/Backend/ClearBit.h"
#include "Rendering/Textures.h"
#include "Rendering/RenderTargets.h"
#include "Rendering/FullscreenQuad.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Programs.h"
#include "Rendering/CommandStream.h"
#include "Rendering/ProgramName.h"
#include "Rendering/Config.h"
#include "Rendering/SSAOPass.h"

// todo:
// change all random generation to make the kernel generations deterministic
// for example by using a instance-based random generator

namespace Rendering {
  namespace SSAOPass {
    static void uploadNoiseKernel() {
      uint8_t size = Config::SSAO::noiseSize;
      uint8_t count = pow(size, 2);
      Quanta::Vector3 kernel[count];
      for(uint8_t i=0; count>i; i++) {
        kernel[i] = {
          Quanta::random()*2-1,
          Quanta::random()*2-1,
          0
        };
        kernel[i].normalize();
      }
      Backend::setTexture(Textures::list.ssaoNoise);
      Backend::writeTexture(size, size, Backend::TextureFormat::SignedNormalizedRGB, kernel);
      Backend::setTexture(0);
    }

    static void uploadSampleKernel() {
      uint8_t size = Config::SSAO::sampleSize;
      Quanta::Vector3 kernel[size];
      for(uint8_t i=0; i<size; ++i) {
        kernel[i] = {
          Quanta::random()*2-1,
          Quanta::random()*2-1,
          Quanta::random()
        };
        kernel[i].normalize();
        float scale = static_cast<float>(i)/size;
        kernel[i] *= Quanta::lerp(0.1, 1, pow(scale, 2));
      }
      Backend::setProgram(Programs::handles[static_cast<size_t>(ProgramName::SSAO)]);
      Backend::setUniformVec3(Uniforms::list.ssaoSampleKernel, size, kernel[0].components);
      Backend::setProgram(0);
    }

    void initialize() {
      uploadNoiseKernel();
      uploadSampleKernel();
    }

    void write(
      CommandStream &stream,
      const Quanta::Matrix4 &worldViewTransform,
      const Quanta::Matrix4 &viewClipTransform,
      const Quanta::Matrix4 &clipWorldTransform
    ) {
      stream.writeRenderTargetSet(RenderTargets::handles.ssao);
      stream.writeClear(static_cast<Backend::ClearBitMask>(Backend::ClearBit::Color));
      stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::SSAO)]);

      stream.writeUniformMat4Set(Uniforms::list.ssaoWorldViewTransform, 1, worldViewTransform.components);
      stream.writeUniformMat4Set(Uniforms::list.ssaoViewClipTransform, 1, viewClipTransform.components);
      stream.writeUniformMat4Set(Uniforms::list.ssaoClipWorldTransform, 1, clipWorldTransform.components);

      stream.writeTextureSet(Uniforms::list.ssaoDepth, Textures::list.geometryDepth, 0);
      stream.writeTextureSet(Uniforms::list.ssaoNoise, Textures::list.ssaoNoise, 1);
      stream.writeTextureSet(Uniforms::list.ssaoNormal, Textures::list.geometryNormal, 2);

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, Backend::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
