#ifndef CLIENT_DIRECTION_STEERING_H
#define CLIENT_DIRECTION_STEERING_H

#include "Simulation/Steering/SteeringEvent.h"
#include "Client/DirectionSteeringConfig.h"
#include "Client/DirectionGroupIndex.h"
#include "Client/DirectionEvent.h"

namespace Client {
  namespace DirectionSteering {
    void initialize();
    void storeEvent(const Simulation::SteeringEvent *steeringEvent);
    void processStartEvent(const DirectionEvent *event);
    void processStopEvent(const DirectionEvent *event);
    void configureGroup(DirectionGroupIndex group, DirectionSteeringConfig config);
  }
}

#endif
