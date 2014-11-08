#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include "Core/Physics/DynamicBody.h"
#include "Quanta/Geometry/TransformationFactory3D.h"
#include "Bro/Bro.h"

static float x = 0;

static void updateForce(Physics::DynamicBody &body) {
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

static void updateOrientation(Physics::DynamicBody &body) {
  x += 0.05;
  Quanta::Vector3 up(0, 1, 0);
  (*body.orientation) = Quanta::TransformationFactory3D::rotation(up, x);
}

void playerControlUpdate(Physics::DynamicBody &body) {
  updateForce(body);
  updateOrientation(body);
}

#endif
