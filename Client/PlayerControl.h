#ifndef CLIENT_PLAYER_CONTROL_H
#define CLIENT_PLAYER_CONTROL_H

#include <math.h>
#include "Physics/DynamicBody.h"
#include "Fixie/TransformFactory.h"
#include "Keyboard.h"
#include "SysKey/Key.h"
#include "Animation/Animator.h"

#include <stdio.h>

namespace Client {
  static void updateForce(Physics::DynamicBody &body, const Keyboard &keyboard) {
    Fixie::Vector3 force = Fixie::Vector3::zero();
    if(keyboard.isDown(SysKey::Key::Right)) {
      force[0] += 1;
    }
    else if(keyboard.isDown(SysKey::Key::Left)) {
      force[0] -= 1;
    }
    if(keyboard.isDown(SysKey::Key::Up)) {
      force[2] += 1;
    }
    else if(keyboard.isDown(SysKey::Key::Down)) {
      force[2] -= 1;
    }

    if(!force.isZero()) {
      force.normalize();
      force *= Fixie::Num(10);
      (*body.force) += force;
    }
  }

  static void updateOrientation(Physics::DynamicBody &body) {
    // todo: should not use floating point
    // should only use Fixie/fixed point
    if(body.velocity->calcSquaredLength() < Fixie::Num(0.01)) return;
    Fixie::Vector3 direction = Fixie::Vector3::normalize(*body.velocity);
    float angle = atan2(static_cast<float>(direction[0])*-1, direction[2]);
    Fixie::Vector3 up(0, 1, 0);
    (*body.orientation) = Fixie::TransformFactory::rotation(up, Fixie::Num(-angle));
  }

  static void updateAnimation(Physics::DynamicBody &body, Animation::Animator &animator) {
    static bool isRunning = false;
    Fixie::Num speed = body.velocity->calcLength();
    Fixie::Num limit = 1.0;
    if(!isRunning && speed > limit) {
      isRunning = true;
      animator.changeAnimation(0, 1);
    }
    else if(isRunning && speed <= limit) {
      isRunning = false;
      animator.changeAnimation(0, 0);
    }
  }

  void playerControlUpdateForce(Physics::DynamicBody &body, const Keyboard &keyboard) {
    updateForce(body, keyboard);
    updateOrientation(body);
  }

  void playerControlReact(Physics::DynamicBody &body, Animation::Animator &animator) {
    updateOrientation(body);
    updateAnimation(body, animator);
  }
}

#endif
