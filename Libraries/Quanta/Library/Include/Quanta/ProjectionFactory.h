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
    static Matrix4 ortho(float left, float right, float bottom, float top, float near, float far) {
      Matrix4 matrix;

      matrix[0] = 2/(right-left);
      matrix[13] = -(right+left)/(right-left);

      matrix[5] = 2/(top-bottom);
      matrix[13] = -(top+bottom)/(top-bottom);

      matrix[10] = 2/(far-near);
      matrix[14] = -(far+near)/(far-near);

      matrix[15] = 1;

      return matrix;
    }
  };
}
