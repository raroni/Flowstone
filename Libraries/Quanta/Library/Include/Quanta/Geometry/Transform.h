#ifndef QUANTA_TRANSFORM_H
#define QUANTA_TRANSFORM_H

#include "Quanta/Math/Quaternion.h"
#include "Quanta/Geometry/Point3D.h"

namespace Quanta {
  class Matrix4;
  class Point3D;

  class Transform {
  public:
    Quaternion orientation = Quaternion::identity();;
    Point3D position;
    Matrix4 getMatrix() const;
    Matrix4 getInverseMatrix();
    Quaternion getOrientation();
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void rotate(Quaternion &rotation);
  };
}

#endif
