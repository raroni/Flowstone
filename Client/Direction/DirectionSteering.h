#ifndef CLIENT_DIRECTION_STEERING_H
#define CLIENT_DIRECTION_STEERING_H

#include "Simulation/Event/SteeringStartEvent.h"
#include "Simulation/Event/SteeringStopEvent.h"
#include "Client/Direction/DirectionSteeringConfig.h"
#include "Client/Direction/DirectionGroupIndex.h"

namespace Client {
  namespace DirectionSteering {
    void processStartEvent(const Simulation::SteeringStartEvent *event);
    void processStopEvent(const Simulation::SteeringStopEvent *event);
    void configureGroup(DirectionGroupIndex group, DirectionSteeringConfig config);
  }
}

#endif
