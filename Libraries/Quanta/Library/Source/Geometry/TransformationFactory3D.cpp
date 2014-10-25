#include <math.h>
#include "Quanta/Math/Matrix4.h"
#include "Quanta/Geometry/Point3D.h"
#include "Quanta/Math/Quaternion.h"
#include "Quanta/Geometry/TransformationFactory3D.h"

namespace Quanta {
  namespace TransformationFactory3D {
    Matrix4 translation(Vector3 translation) {
      Matrix4 matrix = Matrix4::identity();
      matrix[12] = translation[0];
      matrix[13] = translation[1];
      matrix[14] = translation[2];
      return matrix;
    }

    Quaternion rotation(float angle, Vector3 axis) {
      float halfAngle = angle*0.5;
      float real = cos(halfAngle);
      Vector3 imaginaries = axis*sin(halfAngle);
      Quaternion rotation(real, imaginaries);
      return rotation;
    }
  }
}
