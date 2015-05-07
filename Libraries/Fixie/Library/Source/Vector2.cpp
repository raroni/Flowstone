#include "Fixie/Util.h"
#include "Fixie/Vector2.h"

namespace Fixie {
  Vector2::Vector2() { }

  Vector2::Vector2(Num x, Num y) {
    components[0] = x;
    components[1] = y;
  }

  Num& Vector2::operator[](const int index) {
    return components[index];
  }

  const Num& Vector2::operator[](const int index) const {
    return components[index];
  }

  Vector2 Vector2::operator-(const Vector2 &vector) const {
    Vector2 result = *this;
    result -= vector;
    return result;
  }

  Vector2& Vector2::operator-=(Vector2 other) {
    components[0] -= other[0];
    components[1] -= other[1];
    return *this;
  }

  Num Vector2::calcLength() const {
    return Util::sqrt(calcSquaredLength());
  }

  Num Vector2::calcSquaredLength() const {
    return (
      components[0] * components[0] +
      components[1] * components[1]
    );
  }
}
