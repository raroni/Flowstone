#include "Misc/Error.h"
#include "Simulation/Steering/SteeringEvent.h"
#include "Simulation/Steering/SteeringSystem.h"
#include "Simulation/Event/EventSystem.h"
#include "Simulation/Event/EventType.h"
#include "Simulation/Event/SteeringStartEvent.h"
#include "Simulation/Event/SteeringStopEvent.h"
#include "Client/SimulationEventBindings.h"

namespace Client {
  namespace SimulationEventBindings {
    void handleSteeringEvent(const Simulation::SteeringEvent *steeringEvent) {
      switch(steeringEvent->type) {
        case Simulation::SteeringEventType::Start: {
          Simulation::SteeringStartEvent event;
          event.entity = steeringEvent->entity;
          Simulation::EventSystem::report(&event, sizeof(event));
          break;
        }
        case Simulation::SteeringEventType::Stop: {
          Simulation::SteeringStopEvent event;
          event.entity = steeringEvent->entity;
          Simulation::EventSystem::report(&event, sizeof(event));
          break;
        }
        default:
          fatalError("Unknown steering event type.");
      }
    }

    void setup() {
      Simulation::SteeringSystem::setEventHandler(handleSteeringEvent);
    }
  }
}
