#include "Quanta/Math/Matrix4.h"
#include "Quanta/Geometry/TransformFactory3D.h"
#include "Rendering/Config.h"
#include "Rendering/CommandStream.h"
#include "Rendering/Programs.h"
#include "Rendering/Uniforms.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/PointLights.h"

namespace Rendering {
  namespace PointLights {
    const Backend::AttributeLocation positionAttributeLocation = 0;
    Backend::ObjectHandle object;
    Quanta::Matrix4 transforms[Config::maxPointLights];
    Quanta::Vector3 positions[Config::maxPointLights];
    uint8_t count = 0;

    // todo: generate sphere instead of box
    void initialize() {
      object = Backend::createObject();
      Backend::setObject(object);

      Backend::enableAttributeLocation(positionAttributeLocation);

      float vertices[] = {
        -0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        -0.5, -0.5, 0.5,
        0.5, -0.5, 0.5
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
    }

    void write(CommandStream &stream) {
      stream.writeProgramSet(Programs::handles.pointLight);
      stream.writeObjectSet(object);
      for(uint8_t i=0; i<count; ++i) {
        stream.writeUniformMat4Set(Uniforms::list.pointLightModelWorldTransform, 1, transforms[i].components);
        stream.writeIndexedDraw(36, Backend::DataType::UnsignedByte);
      }
    }

    void updatePosition(PointLightIndex index, Quanta::Vector3 position) {
      positions[index] = position;
      transforms[index] = Quanta::TransformFactory3D::translation(position);
    }

    PointLightIndex create() {
      transforms[count] = Quanta::Matrix4::identity();
      return count++;
    }
  }
}
