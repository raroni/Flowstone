#include "Quanta/Math/Matrix4.h"

namespace Quanta {
  class Matrix4;

  class ProjectionFactory {
  public:
    static Matrix4 perspective(float fieldOfView, float aspectRatio, float near, float far) {
      Matrix4 matrix;

      float halfFovTangent = tan(fieldOfView*0.5);

      matrix[0] = 1/halfFovTangent;
      matrix[5] = aspectRatio/halfFovTangent;
      matrix[10] = (far + near) / (far - near);
      matrix[11] = 1;
      matrix[14] = -(2*far*near)/(far-near);

      return matrix;
    }
  };
}
