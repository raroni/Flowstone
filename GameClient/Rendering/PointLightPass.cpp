#include "SysGFX/AttributeLocation.h"
#include "SysGFX/SysGFX.h"
#include "SysGFX/ObjectHandle.h"
#include "Rendering/Programs.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Textures.h"
#include "Rendering/CommandStream.h"
#include "Rendering/PointLightPass.h"

namespace Rendering {
  namespace PointLightPass {
    namespace SphereConfig {
      const uint8_t rings = 14;
      const uint8_t sectors = 10;
    }

    namespace TextureUnits {
      const uint8_t depth = 0;
      const uint8_t normal = 1;
    }

    const uint16_t objectIndexCount = SphereConfig::rings*SphereConfig::sectors*6;
    const SysGFX::AttributeLocation positionAttributeLocation = 0;
    SysGFX::ObjectHandle object;

    void createSphere(float *vertices, uint16_t *indices) {
      float const R = 1./(float)(SphereConfig::rings-1);
      float const S = 1./(float)(SphereConfig::sectors-1);

      uint16_t offset = 0;
      for(int r=0; r<SphereConfig::rings; r++) {
        for(int s=0; s<SphereConfig::sectors; s++) {
          vertices[offset++] = cos(2*M_PI * s * S) * sin(M_PI * r * R);
          vertices[offset++] = sin(-M_PI_2 + M_PI * r * R);
          vertices[offset++] = sin(2*M_PI * s * S) * sin(M_PI * r * R);
        }
      }

      offset = 0;
      for(int r=0; r<SphereConfig::rings; r++) {
        for(int s=0; s<SphereConfig::sectors; s++) {
          const uint16_t i0 = r * SphereConfig::sectors + (s+1);
          const uint16_t i1 = (r+1) * SphereConfig::sectors + (s+1);
          const uint16_t i2 = (r+1) * SphereConfig::sectors + s;
          const uint16_t i3 = r * SphereConfig::sectors + s;

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
      object = SysGFX::createObject();
      SysGFX::setObject(object);

      SysGFX::enableAttributeLocation(positionAttributeLocation);

      float vertices[SphereConfig::rings*SphereConfig::sectors*3];
      uint16_t indices[objectIndexCount];
      createSphere(vertices, indices);

      SysGFX::BufferHandle vertexBuffer = SysGFX::createBuffer();
      SysGFX::setBuffer(SysGFX::BufferTarget::Vertex, vertexBuffer);
      SysGFX::writeBuffer(SysGFX::BufferTarget::Vertex, sizeof(vertices), vertices);
      SysGFX::configureAttribute(positionAttributeLocation, 3, SysGFX::DataType::Float, 0, 0);

      SysGFX::BufferHandle indexBuffer = SysGFX::createBuffer();
      SysGFX::setBuffer(SysGFX::BufferTarget::Index, indexBuffer);
      SysGFX::writeBuffer(SysGFX::BufferTarget::Index, sizeof(indices), indices);

      SysGFX::setObject(0);

      SysGFX::setProgram(Programs::handles.pointLight);
      SysGFX::setUniformInt(Uniforms::list.pointLightDepthTexture, TextureUnits::depth);
      SysGFX::setUniformInt(Uniforms::list.pointLightNormalTexture, TextureUnits::normal);
      SysGFX::setProgram(0);
    }

    void write(CommandStream &stream, const PointLightDrawSet &drawSet, const Quanta::Matrix4 &cameraClipWorldTransform) {
      stream.writeCullFaceSet(SysGFX::CullFace::Front);
      stream.writeEnableBlending();
      stream.writeBlendFunctionSet(SysGFX::BlendFactor::One, SysGFX::BlendFactor::One);
      stream.writeProgramSet(Programs::handles.pointLight);
      stream.writeObjectSet(object);
      stream.writeUniformMat4Set(Uniforms::list.pointLightCameraClipWorldTransform, 1, cameraClipWorldTransform.components);
      stream.writeTexturePairSet(TextureUnits::depth, Textures::list.geometryDepth);
      stream.writeTexturePairSet(TextureUnits::normal, Textures::list.geometryNormal);
      for(uint8_t i=0; i<drawSet.count; ++i) {
        stream.writeUniformVec3Set(Uniforms::list.pointLightWorldPosition, 1, drawSet.positions[i].components);
        stream.writeUniformFloatSet(Uniforms::list.pointLightRadius, 1, &drawSet.radii[i]);
        stream.writeIndexedDraw(objectIndexCount, SysGFX::DataType::UnsignedShort);
      }
      stream.writeDisableBlending();
      stream.writeCullFaceSet(SysGFX::CullFace::Back);
    }

    void handleResolutionChange(Resolution resolution) {
      SysGFX::setProgram(Programs::handles.pointLight);
      const float floatResolution[] = { static_cast<float>(resolution.width), static_cast<float>(resolution.height) };
      SysGFX::setUniformVec2(Uniforms::list.pointLightResolution, 1, floatResolution);
      SysGFX::setProgram(0);
    }
  }
}
