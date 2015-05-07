#include "Fixie/Geometry.h"

namespace Fixie {
  namespace Geometry {
    Fixie::Vector3 createRotated(const Vector3 *vector, const Quaternion *rotation) {
      Quaternion qVector(0, *vector);
      Quaternion result = (*rotation)*qVector;
      result *= Quaternion::createConjugate(rotation);
      return result.imaginaries;
    }
  }
}
