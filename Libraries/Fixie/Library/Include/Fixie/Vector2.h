#ifndef FIXIE_VECTOR2_H
#define FIXIE_VECTOR2_H

#include "Fixie/Num.h"

namespace Fixie {
  class Vector2 {
  public:
    Vector2(Num x, Num y);
    Vector2();
    Num& operator[](const int index);
    const Num& operator[](const int index) const;
    Vector2 operator-(const Vector2 &other) const;
    Vector2& operator-=(Vector2 other);
    Num calcLength() const;
    Num calcSquaredLength() const;
  private:
    Num components[2];
  };
}

#endif
