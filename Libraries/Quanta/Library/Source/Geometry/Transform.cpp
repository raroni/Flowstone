#include "Quanta/Math/Matrix4.h"
#include "Quanta/Geometry/TransformFactory3D.h"
#include "Quanta/Geometry/Transform.h"

namespace Quanta {
  Matrix4 Transform::getMatrix() const {
    Matrix4 orientationMatrix = orientation;
    auto translationMatrix = TransformFactory3D::translation(position);
    return translationMatrix*orientationMatrix;
  }

  Matrix4 Transform::getInverseMatrix() {
    Matrix4 orientationMatrix = orientation.getConjugate();
    auto negatedTranslation = position.getNegated();
    auto translationMatrix = TransformFactory3D::translation(negatedTranslation);

    return orientationMatrix*translationMatrix;
  }

  void Transform::rotateX(float angle) {
    orientation = TransformFactory3D::rotation(Vector3(1, 0, 0), angle) * orientation;
  }

  void Transform::rotateY(float angle) {
    orientation = TransformFactory3D::rotation(Vector3(0, 1, 0), angle) * orientation;
  }

  void Transform::rotateZ(float angle) {
    orientation = TransformFactory3D::rotation(Vector3(0, 0, 1), angle) * orientation;
  }

  void Transform::rotate(Quaternion &rotation) {
    orientation = rotation * orientation;
  }

  Quaternion Transform::getOrientation() {
    return orientation;
  }
}
