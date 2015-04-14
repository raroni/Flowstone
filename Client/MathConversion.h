#ifndef CLIENT_MATH_CONVERSION_H
#define CLIENT_MATH_CONVERSION_H

#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"
#include "Quanta/Math/Matrix4.h"
#include "Fixie/Vector3.h"
#include "Fixie/Quaternion.h"
#include "Fixie/Matrix4.h"

namespace Client {
  namespace MathConversion {
    void convertVector(Quanta::Vector3 &o, const Fixie::Vector3 &i);
    void convertQuaternion(Quanta::Quaternion &o, const Fixie::Quaternion &i);
    void convertMatrix(Quanta::Matrix4 &o, const Fixie::Matrix4 &i);
  }
}

#endif
