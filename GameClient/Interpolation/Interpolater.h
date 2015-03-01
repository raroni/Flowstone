#ifndef INTERPOLATION_INTERPOLATER_H
#define INTERPOLATION_INTERPOLATER_H

#include <stdint.h>
#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"
#include "Interpolation/Index.h"
#include "Common/Physics/DynamicBodyIndex.h"
#include "Quanta/Geometry/TransformFactory3D.h"

namespace Interpolation {
  class Interpolater {
  public:
    void initialize(const Quanta::Vector3 *positions, const Quanta::Quaternion *orientations);
    Index createInterpolation(Physics::DynamicBodyIndex body);
    void reload(const Quanta::Vector3 *newPositions, const Quanta::Quaternion *newOrientations);
    void interpolate(double progress);
    const Quanta::Matrix4* getTransforms() const;
  private:
    Quanta::Vector3 oldPositions[128];
    Quanta::Vector3 newPositions[128];
    Quanta::Quaternion oldOrientations[128];
    Quanta::Quaternion newOrientations[128];
    Quanta::Matrix4 transforms[128];
    uint8_t bodyIndices[128];
    uint8_t bodyCount = 0;
  };
}

#endif
