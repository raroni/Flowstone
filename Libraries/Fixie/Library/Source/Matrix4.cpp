#include "Fixie/Matrix4.h"

namespace Fixie {
  Num& Matrix4::operator[](const int index) {
    return components[index];
  }

  const Num& Matrix4::operator[](const int index) const {
    return components[index];
  }
}
