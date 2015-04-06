#include "Quanta/Math/Vector2.h"

namespace Quanta {
  Vector2::Vector2(float x, float y) {
    components[0] = x;
    components[1] = y;
  }

  float& Vector2::operator[](const int index) {
    return components[index];
  }

  const float& Vector2::operator[](const int index) const {
    return components[index];
  }

  Vector2& Vector2::operator/=(float factor) {
    components[0] /= factor;
    components[1] /= factor;
    return *this;
  }
}
