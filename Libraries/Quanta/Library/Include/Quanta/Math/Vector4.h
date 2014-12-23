#ifndef QUANTA_VECTOR4_H
#define QUANTA_VECTOR4_H

namespace Quanta {
  class Vector4 {
  public:
    Vector4(float x, float y, float z, float w);
    float& operator[](const int index);
    const float& operator[](const int index) const;
    float components[4];
    static Vector4 zero();
  };
}

#endif
