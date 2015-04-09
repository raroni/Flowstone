#include "Fixie/Quaternion.h"

namespace Fixie {
  Quaternion::Quaternion() { }

  Quaternion::Quaternion(Num real, Vector3 imaginaries) {
    this->real = real;
    this->imaginaries = imaginaries;
  }
}
