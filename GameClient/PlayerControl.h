#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include <math.h>
#include "Common/Physics/DynamicBody.h"
#include "Quanta/Geometry/TransformFactory3D.h"
#include "Animation/Animator.h"

static void updateForce(Physics::DynamicBody &body) {
  Quanta::Vector3 force = Quanta::Vector3::zero();
  /*
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
  */

  if(!force.isZero()) {
    force.normalize();
    force *= 10;
    (*body.force) += force;
  }
}

static void updateOrientation(Physics::DynamicBody &body) {
  if(body.velocity->getSquaredLength() < 0.01) return;
  Quanta::Vector3 direction = body.velocity->getNormalized();
  float angle = atan2(direction[0]*-1, direction[2]);
  Quanta::Vector3 up(0, 1, 0);
  (*body.orientation) = Quanta::TransformFactory3D::rotation(up, -angle);
}

static void updateAnimation(Physics::DynamicBody &body, Animation::Animator &animator) {
  static bool isRunning = false;
  float speed = body.velocity->getLength();
  float limit = 1.0;
  if(!isRunning && speed > limit) {
    isRunning = true;
    animator.changeAnimation(0, 1);
  }
  else if(isRunning && speed <= limit) {
    isRunning = false;
    animator.changeAnimation(0, 0);
  }
}

void playerControlUpdateForce(Physics::DynamicBody &body) {
  updateForce(body);
  updateOrientation(body);
}

void playerControlReact(Physics::DynamicBody &body, Animation::Animator &animator) {
  updateOrientation(body);
  updateAnimation(body, animator);
}

#endif
