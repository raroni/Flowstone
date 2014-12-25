#include <math.h>
#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Quaternion.h"
#include "Quanta/Geometry/TransformFactory3D.h"

namespace Quanta {
  namespace TransformFactory3D {
    Matrix4 translation(Vector3 translation) {
      Matrix4 matrix = Matrix4::identity();
      matrix[12] = translation[0];
      matrix[13] = translation[1];
      matrix[14] = translation[2];
      return matrix;
    }

    Quaternion rotation(Vector3 axis, float angle) {
      float halfAngle = angle*0.5;
      float real = cos(halfAngle);
      Vector3 imaginaries = axis*sin(halfAngle);
      Quaternion rotation(real, imaginaries);
      return rotation;
    }

    Matrix4 lookAt(const Vector3 &position, const Vector3 &target, const Vector3 &worldUp) {
      Quanta::Vector3 direction = (target-position).getNormalized();
      Quanta::Vector3 right = Quanta::Vector3::cross(worldUp, direction).getNormalized();
      Quanta::Vector3 up = Quanta::Vector3::cross(direction, right).getNormalized();

      Quanta::Matrix4 result = Quanta::Matrix4::identity();
      result[0] = right[0];
      result[4] = right[1];
      result[8] = right[2];
      result[1] = up[0];
      result[5] = up[1];
      result[9] = up[2];
      result[2] = direction[0];
      result[6] = direction[1];
      result[10] = direction[2];
      result *= Quanta::TransformFactory3D::translation(position*-1);
      return result;
    }
  }
}
