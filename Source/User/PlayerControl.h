#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include "Core/Physics/DynamicBody.h"
#include "Bro/Bro.h"

void playerControlUpdate(Physics::DynamicBody &body) {
  Quanta::Vector3 force = Quanta::Vector3::zero();
  if(broIsKeyPressed(BroKeyRight)) {
    force[0] += 1;
  }
  else if(broIsKeyPressed(BroKeyLeft)) {
    force[0] -= 1;
  }
  if(broIsKeyPressed(BroKeyUp)) {
    force[2] += 1;
  }
  else if(broIsKeyPressed(BroKeyDown)) {
    force[2] -= 1;
  }

  if(!force.isZero()) {
    force.normalize();
    force *= 40;
    (*body.force) += force;
  }
}

#endif
