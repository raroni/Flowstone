#include "Simulation/Session.h"
#include "Client/SimulationTicker.h"

namespace Client {
  namespace SimulationTicker {
    void tick(Simulation::CommandList &commands) {
      Simulation::Session::tick(commands);
      // todo: copy events over here
    }
  }
}
