#ifndef SIMULATION_COMPONENT_TYPE
#define SIMULATION_COMPONENT_TYPE

namespace Simulation {
  enum class ComponentType : uint8_t {
    PhysicsDynamicBody,
    Resource,
    Tag,

    Count
  };
}

#endif
