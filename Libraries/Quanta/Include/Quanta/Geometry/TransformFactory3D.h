namespace Quanta {
  class Vector3;
  class Matrix4;
  class Quaternion;

  namespace TransformFactory3D {
    Matrix4 translation(Vector3 position);
    Quaternion rotation(Vector3 axis, float angle);
    Matrix4 lookAt(const Vector3 &position, const Vector3 &target, const Vector3 &worldUp);
  }
}
