#ifndef FIXIE_VECTOR3_H
#define FIXIE_VECTOR3_H

#include "Fixie/Num.h"

namespace Fixie {
  class Vector3 {
  public:
    Vector3(double x, double y, double z);
    Num& operator[](const int index);
    const Num& operator[](const int index) const;
  private:
    Num components[3];
  };
}

#endif
