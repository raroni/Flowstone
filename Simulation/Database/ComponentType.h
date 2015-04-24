#ifndef SIMULATION_COMPONENT_TYPE
#define SIMULATION_COMPONENT_TYPE

namespace Simulation {
  enum class ComponentType : uint8_t {
    Body,
    SphereCollider,
    ForceDriver,
    Resource,
    Monster,
    Steering,

    Count
  };
}

#endif
