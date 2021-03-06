#ifndef SIMULATION_COMPONENT_TYPE
#define SIMULATION_COMPONENT_TYPE

namespace Simulation {
  enum class ComponentType : uint8_t {
    Body,
    SphereCollider,
    DynamicDriver,
    HarvestResource,
    HarvestWorker,
    Worker,
    Steering,
    Drag,
    Pathfinder,
    AI,
    Actions,
    TicketRequest,
    TicketTarget,
    Targeting,

    Count
  };
}

#endif
