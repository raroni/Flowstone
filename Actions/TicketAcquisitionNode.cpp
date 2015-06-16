#include "Simulation/Database.h"
#include "Actions/TicketAcquisitionNode.h"

namespace Actions {
  namespace TicketAcquisitionNode {
    namespace SimDB = Simulation::Database;
    using namespace Simulation;

    void start(NodeFlow *flow) {
      SimDB::createTicketRequest(flow->getEntityHandle());
    }

    bool isCompleted(NodeFlow *flow) {
      return false;
    }

    uint8_t calcConfigLength(const void *args) { return 0; }
    uint8_t calcStateLength(const void *args) { return 0; }
    void configure(const void *args, void *config) { }
  }
}
