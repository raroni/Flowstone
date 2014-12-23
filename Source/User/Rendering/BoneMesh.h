#ifndef RENDERING_BONE_MESH_H
#define RENDERING_BONE_MESH_H

namespace Rendering {
  struct BoneMesh {
    Backend::ObjectHandle object;
    uint16_t indexCount;
    float boundingRadius;
  };
}

#endif
