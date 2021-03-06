#include "Misc/Error.h"
#include "Simulation/Database.h"
#include "Database/EntityHandle.h"
#include "Simulation/Ticket/TicketRequestList.h"
#include "Simulation/Ticket/TicketRequestHandle.h"
#include "Simulation/Ticket/TicketRequestStatus.h"
#include "Actions/ReachTargetAction.h"
#include "Actions/WoodAcquisitionAction.h"

namespace Actions {
  namespace WoodAcquisitionAction {
    namespace SimDB = Simulation::Database;
    namespace TicketRequestList = Simulation::TicketRequestList;
    typedef Simulation::TicketRequestStatus TicketRequestStatus;
    typedef Simulation::TicketRequestHandle TicketRequestHandle;

    enum class Mode : uint8_t {
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

    struct State {
      Mode mode;
      ReachTargetAction::Options reachOptions;
    };

    uint8_t getStateLength() {
      return sizeof(State);
    }

    uint8_t getOptionsLength() {
      return 0;
    }

    Database::EntityHandle getTarget(Database::EntityHandle entity) {
      TicketRequestHandle handle = SimDB::getTicketRequestHandle(entity);
      uint16_t index = TicketRequestList::getIndex(handle);
      return TicketRequestList::getTarget(index);
    }

    void startMoving(Database::EntityHandle entity, State *state) {
      state->mode = Mode::Moving;

      Database::EntityHandle targetEntity = getTarget(entity);
      Physics::Body targetBody = SimDB::getBody(targetEntity);

      Fixie::Vector2 targetPosition;
      targetPosition[0] = (*targetBody.position)[0];
      targetPosition[1] = (*targetBody.position)[2];

      state->reachOptions = {
        .target = targetPosition,
        .tolerance = Fixie::Num::inverse(8)*Fixie::Num(6)
      };

      ReachTargetAction::startExecution(entity, nullptr, &state->reachOptions);
    }

    void startChopping(Database::EntityHandle entity, State *state) {
      state->mode = Mode::Chopping;
      SimDB::createHarvestWorker(entity, getTarget(entity));
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
      void *options = &state->reachOptions;
      ReachTargetAction::updateExecution(entity, nullptr, options);
      bool completed = ReachTargetAction::isExecuted(entity, nullptr, options);
      if(completed) {
        startChopping(entity, state);
      }
    }

    void updateExecutionChopping(Database::EntityHandle entity, State *state) {

    }

    void startExecution(Database::EntityHandle entity, void *rawState, const void *options) {
      State *state = reinterpret_cast<State*>(rawState);
      state->mode = Mode::Ticketing;
      SimDB::createTicketRequest(entity);
    }

    void updateExecution(Database::EntityHandle entity, void *rawState, const void *options) {
      State *state = reinterpret_cast<State*>(rawState);
      switch(state->mode) {
        case Mode::Ticketing:
          updateExecutionTicketing(entity, state);
          break;
        case Mode::Moving:
          updateExecutionMoving(entity, state);
          break;
        case Mode::Chopping:
          updateExecutionChopping(entity, state);
          break;
        default:
          fatalError("Unknown state.");
      }
    }

    bool isExecuted(Database::EntityHandle entity, void *rawState, const void *options) {
      return false;
    }
  }
}
