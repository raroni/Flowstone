#include "Misc/Error.h"
#include "Simulation/Database.h"
#include "Database/EntityHandle.h"
#include "Simulation/Ticket/TicketRequestList.h"
#include "Simulation/Ticket/TicketRequestHandle.h"
#include "Simulation/Ticket/TicketRequestStatus.h"
#include "Actions3/ReachTargetAction.h"
#include "Actions3/WoodAcquisitionAction.h"

namespace Actions3 {
  namespace WoodAcquisitionAction {
    namespace SimDB = Simulation::Database;
    namespace TicketRequestList = Simulation::TicketRequestList;
    typedef Simulation::TicketRequestStatus TicketRequestStatus;
    typedef Simulation::TicketRequestHandle TicketRequestHandle;

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

    uint8_t getOptionsLength() {
      return 0;
    }

    void startMoving(Database::EntityHandle entity, State *state) {
      *state = State::Moving;

      TicketRequestHandle handle = SimDB::getTicketRequestHandle(entity);
      uint16_t index = TicketRequestList::getIndex(handle);
      Database::EntityHandle targetEntity = TicketRequestList::getTarget(index);

      Physics::Body targetBody = SimDB::getBody(targetEntity);

      Fixie::Vector2 targetPosition;
      targetPosition[0] = (*targetBody.position)[0];
      targetPosition[1] = (*targetBody.position)[2];

      ReachTargetAction::Options options = { .target = targetPosition };

      ReachTargetAction::startExecution(entity, nullptr, &options);
    }

    void updateExecutionTicketing(Database::EntityHandle entity, State *state) {
      TicketRequestHandle handle = SimDB::getTicketRequestHandle(entity);
      uint16_t index = TicketRequestList::getIndex(handle);
      TicketRequestStatus status = TicketRequestList::getStatus(index);
      if(status == TicketRequestStatus::Completed) {
        startMoving(entity, state);
      }
    }

    void updateExecutionMoving(Database::EntityHandle entity, State *state) {

    }

    void startExecution(Database::EntityHandle entity, void *rawState, const void *options) {
      State *state = reinterpret_cast<State*>(rawState);
      *state = State::Ticketing;
      SimDB::createTicketRequest(entity);
    }

    void updateExecution(Database::EntityHandle entity, void *rawState, const void *options) {
      State *state = reinterpret_cast<State*>(rawState);
      switch(*state) {
        case State::Ticketing:
          updateExecutionTicketing(entity, state);
          break;
        case State::Moving:
          updateExecutionMoving(entity, state);
          break;
        default:
          fatalError("Unknown state.");
      }
    }
  }
}
