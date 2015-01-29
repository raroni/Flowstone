#include "Quanta/Math/Matrix4.h"
#include "Quanta/Geometry/TransformFactory3D.h"
#include "Rendering/Config.h"
#include "Rendering/CommandStream.h"
#include "Rendering/Programs.h"
#include "Rendering/Textures.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Backend/CullFace.h"
#include "Rendering/Backend/BlendFactor.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/PointLights.h"

namespace Rendering {
  namespace PointLights {
    struct {
      const uint8_t rings = 14;
      const uint8_t sectors = 10;
    } sphereConfig;
    const uint16_t objectIndexCount = sphereConfig.rings*sphereConfig.sectors*6;
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

    void createSphere(float *vertices, uint16_t *indices) {
      float const R = 1./(float)(sphereConfig.rings-1);
      float const S = 1./(float)(sphereConfig.sectors-1);

      uint16_t offset = 0;
      for(int r=0; r<sphereConfig.rings; r++) {
        for(int s=0; s<sphereConfig.sectors; s++) {
          vertices[offset++] = cos(2*M_PI * s * S) * sin(M_PI * r * R);
          vertices[offset++] = sin(-M_PI_2 + M_PI * r * R);
          vertices[offset++] = sin(2*M_PI * s * S) * sin(M_PI * r * R);
        }
      }

      offset = 0;
      for(int r=0; r<sphereConfig.rings; r++) {
        for(int s=0; s<sphereConfig.sectors; s++) {
          const uint16_t i0 = r * sphereConfig.sectors + (s+1);
          const uint16_t i1 = (r+1) * sphereConfig.sectors + (s+1);
          const uint16_t i2 = (r+1) * sphereConfig.sectors + s;
          const uint16_t i3 = r * sphereConfig.sectors + s;

          indices[offset++] = i0;
          indices[offset++] = i1;
          indices[offset++] = i2;

          indices[offset++] = i0;
          indices[offset++] = i2;
          indices[offset++] = i3;
        }
      }
    }

    void initialize() {
      object = Backend::createObject();
      Backend::setObject(object);

      Backend::enableAttributeLocation(positionAttributeLocation);

      float vertices[sphereConfig.rings*sphereConfig.sectors*3];
      uint16_t indices[objectIndexCount];
      createSphere(vertices, indices);

      Backend::BufferHandle vertexBuffer = Backend::createBuffer();
      Backend::setBuffer(Backend::BufferTarget::Vertex, vertexBuffer);
      Backend::writeBuffer(Backend::BufferTarget::Vertex, sizeof(vertices), vertices);
      Backend::configureAttribute(positionAttributeLocation, 3, Backend::DataType::Float, 0, 0);

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
      stream.writeCullFaceSet(Backend::CullFace::Front);
      stream.writeEnableBlending();
      stream.writeBlendFunctionSet(Backend::BlendFactor::One, Backend::BlendFactor::One);
      stream.writeProgramSet(Programs::handles.pointLight);
      stream.writeObjectSet(object);
      stream.writeUniformMat4Set(Uniforms::list.pointLightCameraClipWorldTransform, 1, cameraClipWorldTransform.components);
      stream.writeTexturePairSet(TextureUnits::depth, Textures::list.geometryDepth);
      stream.writeTexturePairSet(TextureUnits::normal, Textures::list.geometryNormal);
      for(uint8_t i=0; i<count; ++i) {
        stream.writeUniformMat4Set(Uniforms::list.pointLightModelWorldTransform, 1, transforms[i].components);
        stream.writeIndexedDraw(objectIndexCount, Backend::DataType::UnsignedShort);
      }
      stream.writeDisableBlending();
      stream.writeCullFaceSet(Backend::CullFace::Back);
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