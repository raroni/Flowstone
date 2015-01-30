#ifndef RENDERING_STATIC_MESH_INSTANCES_H
#define RENDERING_STATIC_MESH_INSTANCES_H

#include "Quanta/Math/Matrix4.h"
#include "Rendering/Config.h"
#include "Rendering/StaticMeshIndex.h"
#include "Rendering/StaticMeshInstanceHandle.h"

namespace Rendering {
  namespace StaticMeshInstances {
    extern Quanta::Matrix4 transforms[Config::maxStaticMeshInstances];
    extern StaticMeshIndex meshes[Config::maxStaticMeshInstances];
    extern float boundingRadii[Config::maxStaticMeshInstances];
    StaticMeshInstanceHandle create(StaticMeshIndex mesh, float boundingRadius);
    void updateTransform(StaticMeshInstanceHandle handle, const Quanta::Matrix4 &transform);
    uint16_t getCount();
  }
}

#endif
