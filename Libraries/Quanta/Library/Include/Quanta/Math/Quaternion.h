#ifndef QUANTA_QUATERNION_H
#define QUANTA_QUATERNION_H

#include "Quanta/Math/Vector3.h"

namespace Quanta {
  class Matrix4;

  class Quaternion {
    constexpr static float slerpDotThreshold = 0.9995;
  public:
    Quaternion();
    Quaternion(float real, Vector3 imaginaries);
    float real;
    Vector3 imaginaries;
    Quaternion operator*(const Quaternion &other) const;
    Quaternion& operator*=(Quaternion other);
    Quaternion operator-(Quaternion other) const;
    Quaternion& operator-=(Quaternion other);
    Quaternion& operator/=(float divisor);
    static Quaternion identity();
    operator Matrix4() const;
    Quaternion getConjugate();
    static Quaternion slerpWithLimit(Quaternion &origin, Quaternion &destination, float angleLimit);
    static Quaternion slerp(Quaternion origin, const Quaternion &destination, float progress);
    static Quaternion lerp(const Quaternion &origin, const Quaternion &destination, float progress);
    static float dot(const Quaternion &operandA, const Quaternion &operandB);
    Quaternion& operator*=(float factor);
    Quaternion operator*(float factor) const;
    Quaternion& operator+=(Quaternion other);
    Quaternion operator+(Quaternion other) const;
    float getLength() const;
    void normalize();
  };
}

#endif
