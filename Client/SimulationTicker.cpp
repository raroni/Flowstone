#include "Simulation/Session.h"
#include "Client/EventSystem.h"
#include "Client/SimulationTicker.h"

namespace Client {
  namespace SimulationTicker {
    void tick(Simulation::CommandList &commands) {
      Simulation::Session::tick(commands);
      EventSystem::copy();
    }
  }
}
