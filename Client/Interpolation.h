#ifndef CLIENT_INTERPOLATER_H
#define CLIENT_INTERPOLATER_H

#include <stdint.h>
#include "Quanta/Math/Matrix4.h"
#include "Physics/BodyHandle.h"
#include "Physics/BodyList.h"
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"
#include "Client/InterpolationHandle.h"

namespace Client {
  namespace Interpolation {
    void prepare(const Physics::BodyList &bodies);
    InterpolationHandle createInterpolation(Physics::BodyHandle body);
    void reload(const Physics::BodyList &bodies);
    void interpolate(double progress);
    const Quanta::Matrix4* getTransforms();
  };
}

#endif
