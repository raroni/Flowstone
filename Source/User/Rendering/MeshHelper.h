#ifndef RENDERING_MESH_HELPER_H
#define RENDERING_MESH_HELPER_H

#include <stdint.h>
#include "Quanta/Math/Vector3.h"

namespace Rendering {
  namespace MeshHelper {
    float calcBoundingRadius(const Quanta::Vector3 *positions, uint16_t count);
  }
}

#endif
