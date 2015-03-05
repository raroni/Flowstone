#include <stdint.h>
#include <stddef.h>
#include "Quanta/Math/Vector2.h"
#include "Quanta/Math/Vector3.h"
#include "Quanta/Random.h"
#include "Quanta/Util.h"
#include "SysGFX/SysGFX.h"
#include "SysGFX/ClearBit.h"
#include "Rendering/Textures.h"
#include "Rendering/RenderTargets.h"
#include "Rendering/FullscreenQuad.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Programs.h"
#include "Rendering/CommandStream.h"
#include "Rendering/Config.h"
#include "Rendering/SSAOGrainPass.h"

namespace Rendering {
  namespace SSAOGrainPass {
    namespace TextureUnits {
      const uint8_t noise = 0;
      const uint8_t depth = 1;
      const uint8_t normal = 2;
    }

    Quanta::Random random(123978);

    static void uploadNoiseKernel() {
      uint8_t size = Config::SSAO::noiseSize;
      uint8_t count = pow(size, 2);
      Quanta::Vector3 kernel[count];
      for(uint8_t i=0; count>i; i++) {
        kernel[i] = {
          random.get()*2-1,
          random.get()*2-1,
          0
        };
        kernel[i].normalize();
      }
      SysGFX::setTexture(Textures::list.ssaoGrainNoise);
      SysGFX::writeTexture(size, size, SysGFX::TextureFormat::SignedNormalizedRGB, kernel);
      SysGFX::setTexture(0);
    }

    static void uploadSampleKernel() {
      uint8_t size = Config::SSAO::sampleSize;
      Quanta::Vector3 kernel[size];
      for(uint8_t i=0; i<size; ++i) {
        kernel[i] = {
          random.get()*2-1,
          random.get()*2-1,
          random.get()
        };
        kernel[i].normalize();
        float scale = static_cast<float>(i)/size;
        kernel[i] *= Quanta::lerp(0.1, 1, pow(scale, 2));
      }
      SysGFX::setUniformVec3(Uniforms::list.ssaoGrainSampleKernel, size, kernel[0].components);
    }

    static void uploadPerspectiveConfig() {
      SysGFX::setUniformFloat(Uniforms::list.ssaoGrainZNear, 1, &Config::perspective.near);
      SysGFX::setUniformFloat(Uniforms::list.ssaoGrainZFar, 1, &Config::perspective.far);
    }

    static void uploadSampleRadius() {
      float data[] = { Config::SSAO::sampleRadius };
      SysGFX::setUniformFloat(Uniforms::list.ssaoGrainSampleRadius, 1, data);
    }

    static void uploadSampleDifferenceLimit() {
      float data[] = { Config::SSAO::sampleDifferenceLimit };
      SysGFX::setUniformFloat(Uniforms::list.ssaoGrainSampleDifferenceLimit, 1, data);
    }

    static void uploadTextureConfig() {
      SysGFX::setUniformInt(Uniforms::list.ssaoGrainNoiseTexture, TextureUnits::noise);
      SysGFX::setUniformInt(Uniforms::list.ssaoGrainDepthTexture, TextureUnits::depth);
      SysGFX::setUniformInt(Uniforms::list.ssaoGrainNormalTexture, TextureUnits::normal);
    }

    void initialize() {
      SysGFX::setProgram(Programs::handles.ssaoGrain);
      uploadNoiseKernel();
      uploadSampleKernel();
      uploadSampleRadius();
      uploadSampleDifferenceLimit();
      uploadTextureConfig();
      uploadPerspectiveConfig();
      SysGFX::setProgram(0);
    }

    void handleResolutionChange(Resolution resolution) {
      SysGFX::setProgram(Programs::handles.ssaoGrain);
      Quanta::Vector2 noiseScale(resolution.width, resolution.height);
      noiseScale /= static_cast<float>(Config::SSAO::noiseSize);
      SysGFX::setUniformVec2(Uniforms::list.ssaoGrainNoiseScale, 1, noiseScale.components);
      SysGFX::setProgram(0);
    }

    void write(
      CommandStream &stream,
      const Quanta::Matrix4 &clipWorldTransform
    ) {
      stream.writeRenderTargetSet(RenderTargets::handles.ssaoGrain);
      stream.writeClear(static_cast<SysGFX::ClearBitMask>(SysGFX::ClearBit::Color));
      stream.writeProgramSet(Programs::handles.ssaoGrain);

      stream.writeUniformMat4Set(Uniforms::list.ssaoGrainClipWorldTransform, 1, clipWorldTransform.components);

      stream.writeTexturePairSet(TextureUnits::noise, Textures::list.ssaoGrainNoise);
      stream.writeTexturePairSet(TextureUnits::depth, Textures::list.downsampleDepth);
      stream.writeTexturePairSet(TextureUnits::normal, Textures::list.downsampleNormal);

      stream.writeObjectSet(FullscreenQuad::object);
      stream.writeIndexedDraw(6, SysGFX::DataType::UnsignedByte);
      stream.writeObjectSet(0);
    }
  }
}
