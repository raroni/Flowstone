#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include "Core/Physics/DynamicBody.h"

void playerControlUpdate(Physics::DynamicBody &body) {
  (*body.position)[0] += 0.001;
}

#endif
