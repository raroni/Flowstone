#include "Fixie/Vector3.h"

namespace Fixie {
  Vector3::Vector3(double x, double y, double z) {
    components[0] = x;
    components[1] = y;
    components[2] = z;
  }

  Num& Vector3::operator[](const int index) {
    return components[index];
  }

  const Num& Vector3::operator[](const int index) const {
    return components[index];
  }

  Num Vector3::dot(Vector3 a, Vector3 b) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
  }
}
