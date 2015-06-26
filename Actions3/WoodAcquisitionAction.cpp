#include "Simulation/Database.h"
#include "Database/EntityHandle.h"
#include "Actions3/WoodAcquisitionAction.h"

namespace Actions3 {
  namespace WoodAcquisitionAction {
    namespace SimDB = Simulation::Database;

    enum class State : uint8_t {
      Ticketing,
      Moving,
      Chopping,
      Completed,
      CancellingMove,
      CancellingTicket,
      CancellingChop,
      Cancelled,
      Failed
    };

    uint8_t getStateLength() {
      return sizeof(State);
    }

    void startExecution(Database::EntityHandle entity, void *rawState) {
      State *state = reinterpret_cast<State*>(rawState);
      *state = State::Ticketing;
      SimDB::createTicketRequest(entity);
    }

    void updateExecution(Database::EntityHandle entity, void *rawState) {
      State *state = reinterpret_cast<State*>(rawState);
    }
  }
}
