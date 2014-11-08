#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include "Core/Physics/DynamicBody.h"
#include "Bro/Bro.h"

void playerControlUpdate(Physics::DynamicBody &body) {
  if(broIsKeyPressed(BroKeyRight)) {
    (*body.position)[0] += 0.025;
  }
  else if(broIsKeyPressed(BroKeyLeft)) {
    (*body.position)[0] -= 0.025;
  }
}

#endif
