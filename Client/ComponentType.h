#ifndef CLIENT_COMPONENT_TYPE
#define CLIENT_COMPONENT_TYPE

namespace Client {
  enum class ComponentType : uint8_t {
    Interpolation,
    BoneMeshDraw,
    StaticMeshDraw,
    Pose,
    RenderFeed,
    Direction,

    Count
  };
}

#endif
