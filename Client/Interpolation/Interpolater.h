#ifndef CLIENT_INTERPOLATION_INTERPOLATER_H
#define CLIENT_INTERPOLATION_INTERPOLATER_H

#include <stdint.h>
#include "Quanta/Math/Matrix4.h"
#include "Physics/BodyHandle.h"
#include "Physics/BodyList.h"
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"
#include "Client/Interpolation/Index.h"

namespace Client {
  namespace Interpolation {
    class Interpolater {
    public:
      void prepare(const Physics::BodyList &bodies);
      Index createInterpolation(Physics::BodyHandle body);
      void reload(const Physics::BodyList &bodies);
      void interpolate(double progress);
      const Quanta::Matrix4* getTransforms() const;
    private:
      static const uint16_t max = 128;
      Quanta::Vector3 oldPositions[max];
      Quanta::Vector3 newPositions[max];
      Quanta::Quaternion oldOrientations[max];
      Quanta::Quaternion newOrientations[max];
      Quanta::Matrix4 transforms[max];
      Physics::BodyHandle bodyHandles[max];
      uint8_t count = 0;
    };
  }
}

#endif
