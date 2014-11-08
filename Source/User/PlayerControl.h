#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include "Core/Physics/DynamicBody.h"
#include "Bro/Bro.h"

void playerControlUpdate(Physics::DynamicBody &body) {
  if(broIsKeyPressed(BroKeyRight)) {
    (*body.force)[0] += 1;
  }
  else if(broIsKeyPressed(BroKeyLeft)) {
    (*body.force)[0] -= 1;
  }
}

#endif
