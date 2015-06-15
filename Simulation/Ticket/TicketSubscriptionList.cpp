#include "Misc/HandleList.h"
#include "Simulation/Ticket/TicketSubscriptionList.h"

namespace Simulation {
  namespace TicketSubscriptionList {
    static const uint16_t max = 32;
    uint16_t indices[max];
    uint16_t handles[max];
    HandleList handleList(max, indices, handles);

    void create(Physics::BodyHandle handle) {

    }
  }
}
