#ifndef QUANTA_VECTOR3_H
#define QUANTA_VECTOR3_H

namespace Quanta {
  class Vector3 {
  public:
    float components[3];
    Vector3();
    Vector3(float x, float y, float z);
    float& operator[](const int index);
    const float& operator[](const int index) const;
    Vector3 getNegated() const;
    Vector3& operator/=(float divident);
    void negate();
    Vector3& operator*=(float factor);
    Vector3 operator*(float factor) const;
    static float dot(Vector3 operand1, Vector3 operand2);
    static Vector3 cross(Vector3 operand1, Vector3 operand2);
    Vector3 operator+(Vector3 other);
    Vector3& operator+=(Vector3 other);
    Vector3 operator-(const Vector3 other) const;
    Vector3& operator-=(Vector3 other);
    Vector3 getNormalized();
    void normalize();
    float getLength();
    float getSquaredLength();
    void reset();
    static Vector3 zero();
  };
}

#endif
