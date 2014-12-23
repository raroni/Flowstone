#include "Quanta/Math/Vector4.h"

namespace Quanta {
  Vector4::Vector4(float x, float y, float z, float w) {
    components[0] = x;
    components[1] = y;
    components[2] = z;
    components[3] = w;
  }


  float& Vector4::operator[](const int index) {
    return components[index];
  }

  const float& Vector4::operator[](const int index) const {
    return components[index];
  }

  Vector4 Vector4::zero() {
    return Vector4(0, 0, 0, 0);
  }
}
