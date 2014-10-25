namespace Quanta {
  class Vector3;
  class Matrix4;
  class Quaternion;

  namespace TransformationFactory3D {
    Matrix4 translation(Vector3 position);
    Quaternion rotation(float angle, Vector3 axis);
  }
}
