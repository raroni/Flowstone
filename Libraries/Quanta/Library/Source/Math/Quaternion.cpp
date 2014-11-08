#include <math.h>
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Quaternion.h"

namespace Quanta {
  Quaternion::Quaternion() : real(0), imaginaries(Vector3::zero()) { }

  Quaternion::Quaternion(float real, Vector3 imaginaries) : real(real), imaginaries(imaginaries) { }

  Quaternion Quaternion::operator*(Quaternion &other) {
    Quaternion result = *this;
    result *= other;
    return result;
  }

  Quaternion& Quaternion::operator*=(Quaternion other) {
    float resultReal = real*other.real - Vector3::dot(imaginaries, other.imaginaries);
    auto resultImaginaries = other.imaginaries*real + imaginaries*other.real + Vector3::cross(imaginaries, other.imaginaries);
    real = resultReal;
    imaginaries = resultImaginaries;
    return *this;
  }

  Quaternion& Quaternion::operator/=(float divisor) {
    real /= divisor;
    imaginaries /= divisor;
    return *this;
  }

  Quaternion Quaternion::getConjugate() {
    Quaternion conjugate(real, imaginaries.getNegated());
    return conjugate;
  }

  Quaternion::operator Matrix4() {
    auto matrix = Matrix4::identity();
    matrix[0] = 2*(pow(real, 2.0f) + pow(imaginaries[0], 2))-1;
    matrix[1] = 2*(imaginaries[0]*imaginaries[1]+real*imaginaries[2]);
    matrix[2] = 2*(imaginaries[0]*imaginaries[2]-real*imaginaries[1]);

    matrix[4] = 2*(imaginaries[0]*imaginaries[1]-real*imaginaries[2]);
    matrix[5] = 2*(pow(real, 2.0f) + pow(imaginaries[1], 2))-1;
    matrix[6] = 2*(imaginaries[1]*imaginaries[2]+real*imaginaries[0]);

    matrix[8] = 2*(imaginaries[0]*imaginaries[2]+real*imaginaries[1]);
    matrix[9] = 2*(imaginaries[1]*imaginaries[2]-real*imaginaries[0]);
    matrix[10] = 2*(pow(real, 2.0f) + pow(imaginaries[2], 2))-1;

    return matrix;
  }

  float Quaternion::getLength() const {
    return sqrt(real*real + imaginaries[0]*imaginaries[0] + imaginaries[1]*imaginaries[1] + imaginaries[2]*imaginaries[2]);
  }

  Quaternion Quaternion::identity() {
    return Quaternion(1, Vector3(0, 0, 0));
  }

  Quaternion Quaternion::operator*(float factor) {
    Quaternion result = *this;
    result *= factor;
    return result;
  }

  Quaternion& Quaternion::operator*=(float factor) {
    real *= factor;
    imaginaries *= factor;
    return *this;
  }

  Quaternion Quaternion::operator+(Quaternion other) {
    Quaternion result = *this;
    result += other;
    return result;
  }

  Quaternion& Quaternion::operator+=(Quaternion other) {
    real += other.real;
    imaginaries += other.imaginaries;
    return *this;
  }

  Quaternion Quaternion::slerpWithLimit(Quaternion &origin, Quaternion &destination, float angleLimit) {
    float angle = acos(dot(origin, destination));
    float progress = angleLimit > angle ? 1 : angleLimit/angle;

    float inverseSine = 1/sin(angle);

    float q1 = sin(1-progress)*angle*inverseSine;
    float q2 = sin(progress*angle)*inverseSine;

    return origin*q1+destination*q2;
  }

  void Quaternion::normalize() {
    operator/=(getLength());
  }

  Quaternion Quaternion::slerp(Quaternion &origin, Quaternion &destination, float progress) {
    float angle = acos(dot(origin, destination));
    float inverseSine = 1/sin(angle);
    float q1 = sin(1-progress)*angle*inverseSine;
    float q2 = sin(progress*angle)*inverseSine;
    return origin*q1+destination*q2;
  }

  float Quaternion::dot(Quaternion &operandA, Quaternion &operandB) {
    return operandA.real*operandB.real + Vector3::dot(operandA.imaginaries, operandB.imaginaries);
  }
}
