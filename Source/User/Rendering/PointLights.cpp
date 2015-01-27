#include "Quanta/Math/Matrix4.h"
#include "Quanta/Geometry/TransformFactory3D.h"
#include "Rendering/Config.h"
#include "Rendering/CommandStream.h"
#include "Rendering/Programs.h"
#include "Rendering/Textures.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Backend/BlendFactor.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/PointLights.h"

namespace Rendering {
  namespace PointLights {
    const Backend::AttributeLocation positionAttributeLocation = 0;
    Backend::ObjectHandle object;
    Quanta::Matrix4 transforms[Config::maxPointLights];
    Quanta::Vector3 positions[Config::maxPointLights];
    float radii[Config::maxPointLights];
    uint8_t count = 0;
    namespace TextureUnits {
      uint8_t depth = 0;
      uint8_t normal = 1;
    }

    // todo: generate sphere instead of box
    void initialize() {
      object = Backend::createObject();
      Backend::setObject(object);

      Backend::enableAttributeLocation(positionAttributeLocation);

      float vertices[] = {
        -1, 1, -1,
        1, 1, -1,
        -1, -1, -1,
        1, -1, -1,
        -1, 1, 1,
        1, 1, 1,
        -1, -1, 1,
        1, -1, 1
      };
      Backend::BufferHandle vertexBuffer = Backend::createBuffer();
      Backend::setBuffer(Backend::BufferTarget::Vertex, vertexBuffer);
      Backend::writeBuffer(Backend::BufferTarget::Vertex, sizeof(vertices), vertices);
      Backend::configureAttribute(positionAttributeLocation, 3, Backend::DataType::Float, 0, 0);

      uint8_t indices[] = {
        0, 2, 1, 1, 2, 3,
        1, 3, 7, 1, 7, 5,
        4, 7, 6, 4, 5, 7,
        0, 6, 2, 0, 4, 6,
        2, 7, 3, 2, 6, 7,
        5, 0, 1, 5, 4, 0
      };
      Backend::BufferHandle indexBuffer = Backend::createBuffer();
      Backend::setBuffer(Backend::BufferTarget::Index, indexBuffer);
      Backend::writeBuffer(Backend::BufferTarget::Index, sizeof(indices), indices);

      Backend::setObject(0);

      Backend::setProgram(Programs::handles.pointLight);
      Backend::setUniformInt(Uniforms::list.pointLightDepthTexture, TextureUnits::depth);
      Backend::setUniformInt(Uniforms::list.pointLightNormalTexture, TextureUnits::normal);
      Backend::setProgram(0);
    }

    void write(CommandStream &stream, const Quanta::Matrix4 &cameraClipWorldTransform) {
      stream.writeEnableBlending();
      stream.writeBlendFunctionSet(Backend::BlendFactor::One, Backend::BlendFactor::One);
      stream.writeProgramSet(Programs::handles.pointLight);
      stream.writeObjectSet(object);
      stream.writeUniformMat4Set(Uniforms::list.pointLightCameraClipWorldTransform, 1, cameraClipWorldTransform.components);
      stream.writeTexturePairSet(TextureUnits::depth, Textures::list.geometryDepth);
      stream.writeTexturePairSet(TextureUnits::normal, Textures::list.geometryNormal);
      for(uint8_t i=0; i<count; ++i) {
        stream.writeUniformMat4Set(Uniforms::list.pointLightModelWorldTransform, 1, transforms[i].components);
        stream.writeIndexedDraw(36, Backend::DataType::UnsignedByte);
      }
      stream.writeDisableBlending();
    }

    void updateTransform(PointLightIndex index) {
      transforms[index] = Quanta::TransformFactory3D::translation(positions[index]);
      float radius = radii[index];
      transforms[index][0] *= radius;
      transforms[index][5] *= radius;
      transforms[index][10] *= radius;
    }

    void updatePosition(PointLightIndex index, Quanta::Vector3 position) {
      positions[index] = position;
      updateTransform(index);
    }

    void handleResolutionChange(Resolution resolution) {
      Backend::setProgram(Programs::handles.pointLight);
      const float floatResolution[] = { static_cast<float>(resolution.width), static_cast<float>(resolution.height) };
      Backend::setUniformVec2(Uniforms::list.pointLightResolution, 1, floatResolution);
      Backend::setProgram(0);
    }

    PointLightIndex create() {
      positions[count] = Quanta::Vector3::zero();
      radii[count] = 3;
      updateTransform(count);
      return count++;
    }
  }
}
