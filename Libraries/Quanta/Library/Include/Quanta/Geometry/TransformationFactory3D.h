namespace Quanta {
  class Vector3;
  class Matrix4;
  class Quaternion;

  namespace TransformationFactory3D {
    Matrix4 translation(Vector3 position);
    Quaternion rotation(Vector3 axis, float angle);
  }
}
