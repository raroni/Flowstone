#ifndef QUANTA_VECTOR2_H
#define QUANTA_VECTOR2_H

namespace Quanta {
  class Vector2 {
  public:
    float components[2];
    Vector2(float x, float y);
    float& operator[](const int index);
    const float& operator[](const int index) const;
    Vector2& operator/=(float divident);
  };
}

#endif
