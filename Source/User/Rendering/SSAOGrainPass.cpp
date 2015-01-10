#include <stdint.h>
#include <stddef.h>
#include "Quanta/Math/Vector2.h"
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
#include "Rendering/SSAOGrainPass.h"

// todo:
// change all random generation to make the kernel generations deterministic
// for example by using a instance-based random generator

namespace Rendering {
  namespace SSAOGrainPass {
    namespace TextureUnits {
      uint8_t noise = 0;
      uint8_t depth = 1;
      uint8_t normal = 2;
    }

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
      Backend::setTexture(Textures::list.ssaoGrainNoise);
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
      Backend::setUniformVec3(Uniforms::list.ssaoGrainSampleKernel, size, kernel[0].components);
    }

    void uploadSampleRadius() {
      float data[] = { Config::SSAO::sampleRadius };
      Backend::setUniformFloat(Uniforms::list.ssaoGrainSampleRadius, 1, data);
    }

    void uploadSampleDifferenceLimit() {
      float data[] = { Config::SSAO::sampleDifferenceLimit };
      Backend::setUniformFloat(Uniforms::list.ssaoGrainSampleDifferenceLimit, 1, data);
    }

    void uploadTextureConfig() {
      Backend::setUniformInt(Uniforms::list.ssaoGrainNoiseTexture, TextureUnits::noise);
      Backend::setUniformInt(Uniforms::list.ssaoGrainDepthTexture, TextureUnits::depth);
      Backend::setUniformInt(Uniforms::list.ssaoGrainNormalTexture, TextureUnits::normal);
    }

    void initialize() {
      Backend::setProgram(Programs::handles[static_cast<size_t>(ProgramName::SSAOGrain)]);
      uploadNoiseKernel();
      uploadSampleKernel();
      uploadSampleRadius();
      uploadSampleDifferenceLimit();
      uploadTextureConfig();
      Backend::setProgram(0);
    }

    void handleResolutionChange(Resolution resolution) {
      Backend::setProgram(Programs::handles[static_cast<size_t>(ProgramName::SSAOGrain)]);
      Quanta::Vector2 noiseScale(resolution.width, resolution.height);
      noiseScale /= static_cast<float>(Config::SSAO::noiseSize);
      Backend::setUniformVec2(Uniforms::list.ssaoGrainNoiseScale, 1, noiseScale.components);
      Backend::setProgram(0);
    }

    void write(
      CommandStream &stream,
      const Quanta::Matrix4 &worldViewTransform,
      const Quanta::Matrix4 &viewClipTransform,
      const Quanta::Matrix4 &clipWorldTransform
    ) {
      stream.writeRenderTargetSet(RenderTargets::handles.ssaoGrain);
      stream.writeClear(static_cast<Backend::ClearBitMask>(Backend::ClearBit::Color));
      stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::SSAOGrain)]);

      stream.writeUniformMat4Set(Uniforms::list.ssaoGrainWorldViewTransform, 1, worldViewTransform.components);
      stream.writeUniformMat4Set(Uniforms::list.ssaoGrainViewClipTransform, 1, viewClipTransform.components);
      stream.writeUniformMat4Set(Uniforms::list.ssaoGrainClipWorldTransform, 1, clipWorldTransform.components);

      stream.writeTexturePairSet(TextureUnits::noise, Textures::list.ssaoGrainNoise);
      stream.writeTexturePairSet(TextureUnits::depth, Textures::list.downsampleDepth);
      stream.writeTexturePairSet(TextureUnits::normal, Textures::list.downsampleNormal);

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, Backend::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
