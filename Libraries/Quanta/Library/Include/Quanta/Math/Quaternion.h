#ifndef QUANTA_QUATERNION_H
#define QUANTA_QUATERNION_H

#include "Quanta/Math/Vector3.h"

namespace Quanta {
  class Matrix4;

  class Quaternion {
  public:
    Quaternion();
    Quaternion(float real, Vector3 imaginaries);
    float real;
    Vector3 imaginaries;
    Quaternion operator*(Quaternion &other);
    Quaternion& operator*=(Quaternion other);
    Quaternion& operator/=(float divisor);
    static Quaternion identity();
    operator Matrix4();
    Quaternion getConjugate();
    static Quaternion slerpWithLimit(Quaternion &origin, Quaternion &destination, float angleLimit);
    static Quaternion slerp(Quaternion &origin, Quaternion &destination, float progress);
    static float dot(Quaternion &operandA, Quaternion &operandB);
    Quaternion& operator*=(float factor);
    Quaternion operator*(float factor);
    Quaternion& operator+=(Quaternion other);
    Quaternion operator+(Quaternion other);
    float getLength() const;
    void normalize();
  };
}

#endif
