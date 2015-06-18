#include "Simulation/Ticket/TicketRequestList.h"
#include "Simulation/Database.h"
#include "Actions/TicketAcquisitionNode.h"

namespace Actions {
  namespace TicketAcquisitionNode {
    namespace SimDB = Simulation::Database;
    using namespace Simulation;

    void start(NodeCall *call) {
      SimDB::createTicketRequest(call->getFlow()->getEntityHandle());
    }

    bool isCompleted(NodeCall *call) {
      TicketRequestHandle handle = SimDB::getTicketRequestHandle(call->getFlow()->getEntityHandle());
      uint16_t index = TicketRequestList::getIndex(handle);
      TicketRequestStatus status = TicketRequestList::getStatus(index);
      if(status == TicketRequestStatus::Completed) {
        // set up target component
        return true;
      }
    }

    uint8_t calcConfigLength(const void *args) { return 0; }
    uint8_t calcStateLength(const void *args) { return 0; }
    void configure(const void *args, void *config) { }
  }
}
