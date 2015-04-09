#ifndef FIXIE_MATRIX4_H
#define FIXIE_MATRIX4_H

#include "Fixie/Num.h"

namespace Fixie {
  class Matrix4 {
  public:
    Num& operator[](const int index);
    const Num& operator[](const int index) const;
    static Matrix4 identity();
  private:
    Num components[16];
  };
}

#endif
