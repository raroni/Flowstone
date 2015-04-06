#ifndef QUANTA_FRUSTUM_H
#define QUANTA_FRUSTUM_H

#include "Quanta/Geometry/Plane.h"

namespace Quanta {
  struct Frustum {
    enum PlaneName {
      Far,
      Near,
      Right,
      Left,
      Top,
      Bottom
    };

    Plane planes[6];
  };
}

#endif
