#include "Fixie/Util.h"
#include "Fixie/Quaternion.h"

namespace Fixie {
  Quaternion::Quaternion() { }

  Quaternion::Quaternion(Num real, Vector3 imaginaries) {
    this->real = real;
    this->imaginaries = imaginaries;
  }

  Quaternion Quaternion::operator*(const Quaternion &other) const {
    Quaternion result = *this;
    result *= other;
    return result;
  }

  Quaternion& Quaternion::operator*=(Quaternion other) {
    Num resultReal = real*other.real - Vector3::dot(imaginaries, other.imaginaries);
    Vector3 resultImaginaries = other.imaginaries*real + imaginaries*other.real + Vector3::cross(imaginaries, other.imaginaries);
    real = resultReal;
    imaginaries = resultImaginaries;
    return *this;
  }

  Quaternion Quaternion::operator*(Num scalar) const {
    Quaternion result = *this;
    result *= scalar;
    return result;
  }

  Quaternion& Quaternion::operator*=(Num scalar) {
    real *= scalar;
    imaginaries *= scalar;
    return *this;
  }

  Quaternion& Quaternion::operator/=(Num scalar) {
    real /= scalar;
    imaginaries /= scalar;
    return *this;
  }

  Quaternion Quaternion::operator+(Quaternion other) const {
    Quaternion result = *this;
    result += other;
    return result;
  }

  Quaternion& Quaternion::operator+=(Quaternion other) {
    real += other.real;
    imaginaries += other.imaginaries;
    return *this;
  }

  Num Quaternion::calcLength() const {
    return Util::sqrt(
      real*real +
      imaginaries[0]*imaginaries[0] +
      imaginaries[1]*imaginaries[1] +
      imaginaries[2]*imaginaries[2]
    );
  }

  void Quaternion::normalize() {
    operator/=(calcLength());
  }

  Quaternion Quaternion::identity() {
    return Quaternion(1, Vector3(0, 0, 0));
  }
}
