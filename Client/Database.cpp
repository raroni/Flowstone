#include "Database/EntityManager.h"
#include "Interpolation/Interpolater.h"
#include "Database/ComponentManager.h"
#include "Animation/Animator.h"
#include "Client/ComponentType.h"
#include "Client/Database.h"

namespace Client {
  namespace Database {
    using namespace ::Database;

    const uint16_t entityMax = 128;
    const uint16_t componentMax = 32;

    EntityHandle entityHandles[entityMax];
    EntityManager entityManager(entityHandles, entityMax);

    ComponentHandle componentHandles[entityMax*componentMax];
    BitSet32 componentExistances[entityMax];
    ComponentManager componentManager(componentHandles, componentExistances, componentMax);

    EntityHandle createEntity() {
      return entityManager.create();
    }

    uint8_t convertTypeToInt(ComponentType type) {
      return static_cast<uint8_t>(type);
    }

    void linkComponent(EntityHandle entity, ComponentType type, ComponentHandle component) {
      componentManager.link(entity, convertTypeToInt(type), component);
    }

    void unlinkComponent(EntityHandle entity, ComponentType type) {
      componentManager.unlink(entity, convertTypeToInt(type));
    }

    ComponentHandle getComponent(EntityHandle entity, ComponentType type) {
      return componentManager.get(entity, convertTypeToInt(type));
    }

    bool hasComponent(EntityHandle entity, ComponentType type) {
      return componentManager.has(entity, convertTypeToInt(type));
    }

    Animation::PoseIndex createPose(EntityHandle entity, Animation::SkeletonHandle skeleton) {
      union {
        Animation::PoseIndex poseHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.poseHandle = Animation::animator.createPose(skeleton);
      linkComponent(entity, ComponentType::Pose, caster.genericHandle);
      return caster.poseHandle;
    }

    Interpolation::Handle createInterpolation(::Database::EntityHandle entity, Physics::BodyHandle physicsBody) {
      union {
        Interpolation::Handle interpolationHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.interpolationHandle = Interpolation::interpolater.createInterpolation(physicsBody);
      linkComponent(entity, ComponentType::Interpolation, caster.genericHandle);
      return caster.interpolationHandle;
    }
  }
}
