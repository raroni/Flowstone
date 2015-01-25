#include "Rendering/Backend/Functions.h"
#include "Rendering/AttributeLocation.h"
#include "Rendering/Backend/AttributeLocation.h"
#include "Rendering/FullscreenQuad.h"

namespace Rendering {
  namespace FullscreenQuad {
    Backend::ObjectHandle object;

    void initialize() {
      object = Backend::createObject();
      Backend::setObject(object);

      Backend::enableAttributeLocation(static_cast<Backend::AttributeLocation>(AttributeLocation::Position));

      float vertices[] = {
        -1, -1,
        1, -1,
        -1, 1,
        1, 1
      };
      Backend::BufferHandle vertexBuffer = Backend::createBuffer();
      Backend::setBuffer(Backend::BufferTarget::Vertex, vertexBuffer);
      Backend::writeBuffer(Backend::BufferTarget::Vertex, sizeof(vertices), vertices);
      Backend::configureAttribute(static_cast<Backend::AttributeLocation>(AttributeLocation::Position), 2, Backend::DataType::Float, 0, 0);

      uint8_t indices[] = { 0, 1, 2, 2, 1, 3 };
      Backend::BufferHandle indexBuffer = Backend::createBuffer();
      Backend::setBuffer(Backend::BufferTarget::Index, indexBuffer);
      Backend::writeBuffer(Backend::BufferTarget::Index, sizeof(indices), indices);

      Backend::setObject(0);
    }
  }
}
