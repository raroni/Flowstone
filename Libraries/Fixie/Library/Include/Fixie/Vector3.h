#ifndef FIXIE_VECTOR3_H
#define FIXIE_VECTOR3_H

#include "Fixie/Num.h"

namespace Fixie {
  class Vector3 {
  public:
    Vector3(double x, double y, double z);
    Vector3();
    Num& operator[](const int index);
    const Num& operator[](const int index) const;
    Vector3 operator+(Vector3 other);
    Vector3& operator+=(Vector3 other);
    static Num dot(Vector3 a, Vector3 b);
    static Vector3 cross(Vector3 a, Vector3 b);
  private:
    Num components[3];
  };
}

#endif
