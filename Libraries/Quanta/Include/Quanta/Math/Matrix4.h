#ifndef QUANTA_MATRIX4_H
#define QUANTA_MATRIX4_H

namespace Quanta {
  class Vector4;

  class Matrix4 {
  public:
    float components[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    static Matrix4 identity();
    float& operator[](const int index);
    Vector4 operator*(Vector4 matrix) const;
    const float& operator[](const int index) const;
    Matrix4 operator*(Matrix4 matrix);
    Matrix4& operator*=(Matrix4 matrix);
    Matrix4 getInverted() const;
    void reset();
    void invert();
  };
}

#endif
