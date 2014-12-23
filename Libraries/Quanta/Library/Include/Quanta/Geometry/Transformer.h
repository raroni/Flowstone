#ifndef QUANTA_TRANSFORMER_H
#define QUANTA_TRANSFORMER_H

namespace Quanta {
  class Matrix4;
  class Vector4;
  struct Frustum;

  namespace Transformer {
    void updateFrustum(Frustum &frustum, const Matrix4 &transform);
    void updateVector4(Vector4 &vector, const Matrix4 &transform);
  }
}

#endif
