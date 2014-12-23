#include <stdint.h>
#include "Quanta/Geometry/Frustum.h"
#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Vector4.h"
#include "Quanta/Geometry/Transformer.h"

namespace Quanta {
  namespace Transformer {
    void updateVector4(Vector4 &vector, const Matrix4 &transform) {
      vector = transform*vector;
    }

    void updatePlane(Plane &plane, const Matrix4 &transform) {
      Quanta::Vector4 normal = Quanta::Vector4(plane.normal[0], plane.normal[1], plane.normal[2], 0);
      Quanta::Vector4 position = Quanta::Vector4(plane.position[0], plane.position[1], plane.position[2], 1);
      updateVector4(normal, transform);
      updateVector4(position, transform);

      plane.position[0] = position[0];
      plane.position[1] = position[1];
      plane.position[2] = position[2];
      plane.normal[0] = normal[0];
      plane.normal[1] = normal[1];
      plane.normal[2] = normal[2];
    }

    void updateFrustum(Frustum &frustum, const Matrix4 &transform) {
      for(uint8_t i=0; 6>i; i++) {
        updatePlane(frustum.planes[i], transform);
      }
    }
  }
}
