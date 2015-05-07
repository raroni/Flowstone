#ifndef FIXIE_QUATERNION_H
#define FIXIE_QUATERNION_H

#include "Fixie/Num.h"
#include "Fixie/Vector3.h"

namespace Fixie {
  class Quaternion {
  public:
    Quaternion();
    Quaternion(Num real, Vector3 imaginaries);
    Quaternion operator*(const Quaternion &other) const;
    Quaternion& operator*=(Quaternion other);
    Quaternion operator*(Num scalar) const;
    Quaternion& operator*=(Num scalar);
    Quaternion& operator+=(Quaternion other);
    Quaternion operator+(Quaternion other) const;
    Num real;
    Vector3 imaginaries;
    static Quaternion identity();
  };
}

#endif
