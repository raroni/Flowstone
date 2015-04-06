#ifndef QUANTA_TRANSFORM_H
#define QUANTA_TRANSFORM_H

#include "Quanta/Math/Quaternion.h"
#include "Quanta/Math/Vector3.h"

namespace Quanta {
  class Matrix4;

  class Transform {
  public:
    Quaternion orientation = Quaternion::identity();;
    Vector3 position;
    Matrix4 calcMatrix() const;
    Matrix4 calcInverseMatrix();
    Quaternion getOrientation();
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void rotate(Quaternion &rotation);
  };
}

#endif
