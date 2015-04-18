#ifndef SIMULATION_COMPONENT_TYPE
#define SIMULATION_COMPONENT_TYPE

namespace Simulation {
  enum class ComponentType : uint8_t {
    PhysicsDynamicBody,
    PhysicsStaticBody,
    PhysicsStaticSphereCollider,
    PhysicsDynamicSphereCollider,
    Resource,
    Monster,

    Count
  };
}

#endif
