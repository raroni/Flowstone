#include "SysGFX/SysGFX.h"
#include "Rendering/AttributeLocation.h"
#include "SysGFX/AttributeLocation.h"
#include "Rendering/FullscreenQuad.h"

namespace Rendering {
  namespace FullscreenQuad {
    SysGFX::ObjectHandle object;

    void initialize() {
      object = SysGFX::createObject();
      SysGFX::setObject(object);

      SysGFX::enableAttributeLocation(static_cast<SysGFX::AttributeLocation>(AttributeLocation::Position));

      float vertices[] = {
        -1, -1,
        1, -1,
        -1, 1,
        1, 1
      };
      SysGFX::BufferHandle vertexBuffer = SysGFX::createBuffer();
      SysGFX::setBuffer(SysGFX::BufferTarget::Vertex, vertexBuffer);
      SysGFX::writeBuffer(SysGFX::BufferTarget::Vertex, sizeof(vertices), vertices);
      SysGFX::configureAttribute(static_cast<SysGFX::AttributeLocation>(AttributeLocation::Position), 2, SysGFX::DataType::Float, 0, 0);

      uint8_t indices[] = { 0, 1, 2, 2, 1, 3 };
      SysGFX::BufferHandle indexBuffer = SysGFX::createBuffer();
      SysGFX::setBuffer(SysGFX::BufferTarget::Index, indexBuffer);
      SysGFX::writeBuffer(SysGFX::BufferTarget::Index, sizeof(indices), indices);

      SysGFX::setObject(0);
    }
  }
}
