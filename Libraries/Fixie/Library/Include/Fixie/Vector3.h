#ifndef FIXIE_VECTOR3_H
#define FIXIE_VECTOR3_H

#include "Fixie/Num.h"

namespace Fixie {
  class Vector3 {
  public:
    Vector3(Num x, Num y, Num z);
    Vector3();
    Num& operator[](const int index);
    const Num& operator[](const int index) const;
    Vector3 operator+(const Vector3 &other) const;
    Vector3& operator+=(Vector3 other);
    Vector3 operator-(const Vector3 &other) const;
    Vector3& operator-=(Vector3 other);
    Vector3 operator*(const Num divisor) const;
    Vector3& operator*=(Num divisor);
    Vector3 operator/(Num divisor) const;
    Vector3& operator/=(Num divisor);
    void normalize();
    Num calcLength() const;
    Num calcSquaredLength() const;
    void reset();
    bool isZero() const;
    static Num dot(Vector3 a, Vector3 b);
    static Vector3 cross(Vector3 a, Vector3 b);
    static Vector3 normalize(Vector3 v);
    static Vector3 zero();
  private:
    Num components[3];
  };
}

#endif
