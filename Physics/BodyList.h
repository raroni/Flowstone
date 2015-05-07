#ifndef PHYSICS_BODY_LIST_H
#define PHYSICS_BODY_LIST_H

#include "Fixie/Quaternion.h"
#include "Fixie/Vector3.h"
#include "Physics/Config.h"
#include "Physics/ConstBody.h"
#include "Physics/Body.h"
#include "Physics/BodyHandle.h"

namespace Physics {
  class BodyList {
  public:
    BodyHandle create();
    Body get(BodyHandle handle);
    ConstBody get(BodyHandle handle) const;
    uint16_t getIndex(BodyHandle handle) const;
    uint16_t getCount() const;
    Fixie::Vector3 positions[Config::bodyMax];
    Fixie::Quaternion orientations[Config::bodyMax];
    Fixie::Vector3 velocities[Config::bodyMax];
    Fixie::Vector3 spins[Config::bodyMax];
  private:
    uint16_t count = 0;
  };
}

#endif
