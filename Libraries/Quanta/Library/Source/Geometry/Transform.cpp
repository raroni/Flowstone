#include "Quanta/Math/Matrix4.h"
#include "Quanta/Geometry/TransformationFactory3D.h"
#include "Quanta/Geometry/Transform.h"

namespace Quanta {
  Matrix4 Transform::getMatrix() {
    Matrix4 orientationMatrix = orientation;
    auto translationMatrix = TransformationFactory3D::translation(position.getVector());
    return translationMatrix*orientationMatrix;
  }

  Matrix4 Transform::getInverseMatrix() {
    Matrix4 orientationMatrix = orientation.getConjugate();
    auto negatedTranslation = position.getVector().getNegated();
    auto translationMatrix = TransformationFactory3D::translation(negatedTranslation);

    return orientationMatrix*translationMatrix;
  }

  void Transform::rotateX(float angle) {
    orientation = TransformationFactory3D::rotation(angle, Vector3(1, 0, 0)) * orientation;
  }

  void Transform::rotateY(float angle) {
    orientation = TransformationFactory3D::rotation(angle, Vector3(0, 1, 0)) * orientation;
  }

  void Transform::rotateZ(float angle) {
    orientation = TransformationFactory3D::rotation(angle, Vector3(0, 0, 1)) * orientation;
  }

  void Transform::rotate(Quaternion &rotation) {
    orientation = rotation * orientation;
  }

  Quaternion Transform::getOrientation() {
    return orientation;
  }
}
