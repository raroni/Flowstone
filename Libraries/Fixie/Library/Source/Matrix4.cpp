#include "Fixie/Matrix4.h"

namespace Fixie {
  Num& Matrix4::operator[](const int index) {
    return components[index];
  }

  const Num& Matrix4::operator[](const int index) const {
    return components[index];
  }

  Matrix4 Matrix4::identity() {
    Matrix4 matrix;

    matrix[0] = 1;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;
    matrix[4] = 0;
    matrix[5] = 1;
    matrix[6] = 0;
    matrix[7] = 0;
    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = 1;
    matrix[11] = 0;
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;

    return matrix;
  }
}
