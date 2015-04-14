#ifndef CLIENT_INTERPOLATION_INTERPOLATER_H
#define CLIENT_INTERPOLATION_INTERPOLATER_H

#include <stdint.h>
#include "Fixie/Matrix4.h"
#include "Fixie/Vector3.h"
#include "Fixie/Quaternion.h"
#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"
#include "Physics/DynamicBodyIndex.h"
#include "Client/Interpolation/Index.h"

namespace Client {
  namespace Interpolation {
    class Interpolater {
    public:
      void initialize(const Fixie::Vector3 *positions, const Fixie::Quaternion *orientations);
      Index createInterpolation(Physics::DynamicBodyIndex body);
      void reload(const Fixie::Vector3 *newPositions, const Fixie::Quaternion *newOrientations);
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
}

#endif
