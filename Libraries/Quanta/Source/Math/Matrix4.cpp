#include "Quanta/Math/Vector4.h"
#include "Quanta/Math/Matrix4.h"

namespace Quanta {
  float& Matrix4::operator[](const int index) {
    return components[index];
  }

  const float& Matrix4::operator[](const int index) const {
    return components[index];
  }

  Matrix4 Matrix4::identity() {
    Matrix4 matrix;
    matrix[0] = 1;
    matrix[5] = 1;
    matrix[10] = 1;
    matrix[15] = 1;

    return matrix;
  }

  Vector4 Matrix4::operator*(Vector4 vector) const {
    Vector4 result = Vector4::zero();

    for(int row=0; 4>row; row++) {
      for(int step=0; 4>step; step++) {
        result[row] += components[step*4+row] * vector[step];
      }
    }

    return result;
  }

  Matrix4 Matrix4::getInverted() const {
    Matrix4 result = *this;
    result.invert();
    return result;
  }

  // borrowed from http://www.mesa3d.org/
  void Matrix4::invert() {
    float inv[16];

    inv[0] = components[5]  * components[10] * components[15] -
             components[5]  * components[11] * components[14] -
             components[9]  * components[6]  * components[15] +
             components[9]  * components[7]  * components[14] +
             components[13] * components[6]  * components[11] -
             components[13] * components[7]  * components[10];

    inv[4] = -components[4]  * components[10] * components[15] +
              components[4]  * components[11] * components[14] +
              components[8]  * components[6]  * components[15] -
              components[8]  * components[7]  * components[14] -
              components[12] * components[6]  * components[11] +
              components[12] * components[7]  * components[10];

    inv[8] = components[4]  * components[9] * components[15] -
             components[4]  * components[11] * components[13] -
             components[8]  * components[5] * components[15] +
             components[8]  * components[7] * components[13] +
             components[12] * components[5] * components[11] -
             components[12] * components[7] * components[9];

    inv[12] = -components[4]  * components[9] * components[14] +
               components[4]  * components[10] * components[13] +
               components[8]  * components[5] * components[14] -
               components[8]  * components[6] * components[13] -
               components[12] * components[5] * components[10] +
               components[12] * components[6] * components[9];

    inv[1] = -components[1]  * components[10] * components[15] +
              components[1]  * components[11] * components[14] +
              components[9]  * components[2] * components[15] -
              components[9]  * components[3] * components[14] -
              components[13] * components[2] * components[11] +
              components[13] * components[3] * components[10];

    inv[5] = components[0]  * components[10] * components[15] -
             components[0]  * components[11] * components[14] -
             components[8]  * components[2] * components[15] +
             components[8]  * components[3] * components[14] +
             components[12] * components[2] * components[11] -
             components[12] * components[3] * components[10];

    inv[9] = -components[0]  * components[9] * components[15] +
              components[0]  * components[11] * components[13] +
              components[8]  * components[1] * components[15] -
              components[8]  * components[3] * components[13] -
              components[12] * components[1] * components[11] +
              components[12] * components[3] * components[9];

    inv[13] = components[0]  * components[9] * components[14] -
              components[0]  * components[10] * components[13] -
              components[8]  * components[1] * components[14] +
              components[8]  * components[2] * components[13] +
              components[12] * components[1] * components[10] -
              components[12] * components[2] * components[9];

    inv[2] = components[1]  * components[6] * components[15] -
             components[1]  * components[7] * components[14] -
             components[5]  * components[2] * components[15] +
             components[5]  * components[3] * components[14] +
             components[13] * components[2] * components[7] -
             components[13] * components[3] * components[6];

    inv[6] = -components[0]  * components[6] * components[15] +
              components[0]  * components[7] * components[14] +
              components[4]  * components[2] * components[15] -
              components[4]  * components[3] * components[14] -
              components[12] * components[2] * components[7] +
              components[12] * components[3] * components[6];

    inv[10] = components[0]  * components[5] * components[15] -
              components[0]  * components[7] * components[13] -
              components[4]  * components[1] * components[15] +
              components[4]  * components[3] * components[13] +
              components[12] * components[1] * components[7] -
              components[12] * components[3] * components[5];

    inv[14] = -components[0]  * components[5] * components[14] +
               components[0]  * components[6] * components[13] +
               components[4]  * components[1] * components[14] -
               components[4]  * components[2] * components[13] -
               components[12] * components[1] * components[6] +
               components[12] * components[2] * components[5];

    inv[3] = -components[1] * components[6] * components[11] +
              components[1] * components[7] * components[10] +
              components[5] * components[2] * components[11] -
              components[5] * components[3] * components[10] -
              components[9] * components[2] * components[7] +
              components[9] * components[3] * components[6];

    inv[7] = components[0] * components[6] * components[11] -
             components[0] * components[7] * components[10] -
             components[4] * components[2] * components[11] +
             components[4] * components[3] * components[10] +
             components[8] * components[2] * components[7] -
             components[8] * components[3] * components[6];

    inv[11] = -components[0] * components[5] * components[11] +
               components[0] * components[7] * components[9] +
               components[4] * components[1] * components[11] -
               components[4] * components[3] * components[9] -
               components[8] * components[1] * components[7] +
               components[8] * components[3] * components[5];

    inv[15] = components[0] * components[5] * components[10] -
              components[0] * components[6] * components[9] -
              components[4] * components[1] * components[10] +
              components[4] * components[2] * components[9] +
              components[8] * components[1] * components[6] -
              components[8] * components[2] * components[5];

    float det = components[0] * inv[0] + components[1] * inv[4] + components[2] * inv[8] + components[3] * inv[12];
    det = 1.0 / det;
    for(int i = 0; i < 16; i++) {
      components[i] = inv[i] * det;
    }
  }

  Matrix4& Matrix4::operator*=(Matrix4 other) {
    Matrix4 original = *this;
    reset();

    int resultIndex;
    for(int row=0; 4>row; row++) {
      for(int column=0; 4>column; column++) {
        resultIndex = column*4+row;
        for(int step=0; 4>step; step++) {
          components[resultIndex] += original[row+step*4] * other[column*4+step];
        }
      }
    }

    return *this;
  }

  void Matrix4::reset() {
    for(int i=0; 16>i; i++) {
      components[i] = 0;
    }
  }

  Matrix4 Matrix4::operator*(Matrix4 other) {
    Matrix4 result = *this;
    result *= other;
    return result;
  }
}
