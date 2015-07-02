#ifndef SIMULATION_STEERING_SYSTEM_H
#define SIMULATION_STEERING_SYSTEM_H

#include "Database/EntityHandle.h"
#include "Simulation/Steering/Steering.h"
#include "Simulation/Steering/SteeringEventHandler.h"
#include "Simulation/Steering/SteeringHandle.h"

namespace Simulation {
  namespace SteeringSystem {
    SteeringHandle create(::Database::EntityHandle entity, Physics::DynamicDriverHandle physicsDriver);
    void destroy(SteeringHandle handle);
    Steering get(SteeringHandle handle);
    void update();
    void setEventHandler(SteeringEventHandler func);
  }
}

#endif
