#include "Simulation/Ticket/TicketRequestList.h"
#include "Simulation/Ticket/TicketTargetList.h"
#include "Simulation/Ticket/TicketRequestStatus.h"
#include "Simulation/Ticket/TicketTargetStatus.h"
#include "Simulation/Ticket/TicketSystem.h"

namespace Simulation {
  namespace TicketSystem {
    namespace RequestList = TicketRequestList;
    namespace TargetList = TicketTargetList;
    typedef TicketRequestStatus RequestStatus;
    typedef TicketTargetStatus TargetStatus;

    TicketRequestHandle createRequest(Physics::BodyHandle handle) {
      return RequestList::create(handle);
    }

    TicketTargetHandle createTarget(Database::EntityHandle handle) {
      return TargetList::create(handle);
    }

    void destroyTarget(TicketTargetHandle handle) {
      TargetList::destroy(handle);
    }

    void update() {
      uint16_t targetCount = TargetList::getCount();
      for(uint16_t ti=0; ti<targetCount; ++ti) {
        TargetStatus targetStatus = TargetList::getStatus(ti);
        if(targetStatus == TargetStatus::Free) {
          uint16_t requestCount = RequestList::getCount();
          for(uint16_t ri=0; ri<requestCount; ++ri) {
            RequestStatus requestStatus = RequestList::getStatus(ri);
            if(requestStatus == RequestStatus::Waiting) {
              Database::EntityHandle targetEntity = TargetList::getEntityHandle(ti);
              RequestList::updateTarget(ri, targetEntity);
              RequestList::updateStatus(ri, RequestStatus::Completed);
              TargetList::updateStatus(ti, TargetStatus::Taken);
              break;
            }
          }
        }
      }
    }
  }
}
