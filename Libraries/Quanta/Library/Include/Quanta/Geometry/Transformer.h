#ifndef QUANTA_TRANSFORMER_H
#define QUANTA_TRANSFORMER_H

namespace Quanta {
  class Matrix4;
  struct Frustum;

  namespace Transformer {
    void updateFrustum(Frustum &frustum, const Matrix4 &transform);
  }
}

#endif
