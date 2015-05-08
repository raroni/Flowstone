#include "Database/EntityManager.h"
#include "Rendering/Renderer.h"
#include "Interpolation/Interpolater.h"
#include "Database/ComponentManager.h"
#include "Animation/Animator.h"
#include "Client/Direction.h"
#include "Client/RenderFeed.h"
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

    Rendering::BoneMeshInstanceHandle createBoneMeshInstance(EntityHandle entity, Rendering::BoneMeshIndex mesh) {
      union {
        Rendering::BoneMeshInstanceHandle instanceHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.instanceHandle = Rendering::renderer.createBoneMeshInstance(mesh);
      linkComponent(entity, ComponentType::BoneMeshInstance, caster.genericHandle);
      return caster.instanceHandle;
    }

    Rendering::StaticMeshInstanceHandle createStaticMeshInstance(::Database::EntityHandle entity, Rendering::StaticMeshIndex mesh) {
      union {
        Rendering::StaticMeshInstanceHandle instanceHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.instanceHandle = Rendering::renderer.createStaticMeshInstance(mesh);
      linkComponent(entity, ComponentType::StaticMeshInstance, caster.genericHandle);
      return caster.instanceHandle;
    }

    void createRenderFeed(EntityHandle entity) {
      assert(hasComponent(entity, ComponentType::Interpolation));
      assert(hasComponent(entity, ComponentType::Pose));
      assert(hasComponent(entity, ComponentType::BoneMeshInstance));

      union {
        uint16_t renderFeedHandle; // todo: Use proper type instead of just generic uint16_t
        ComponentHandle genericHandle;
      } caster;
      Interpolation::Handle interpolationHandle = getInterpolation(entity);
      Animation::PoseIndex poseHandle = getPoseHandle(entity);
      Rendering::BoneMeshInstanceHandle boneMeshInstanceHandle = getBoneMeshInstanceHandle(entity);
      caster.renderFeedHandle = RenderFeed::createBoneMeshFeed(interpolationHandle, poseHandle, boneMeshInstanceHandle);
      linkComponent(entity, ComponentType::RenderFeed, caster.genericHandle);
      //return caster.renderFeedHandle;
    }

    DirectionHandle createDirection(EntityHandle clientEntity, EntityHandle simEntity, DirectionGroupHandle group) {
      union {
        DirectionHandle directionHandle;
        ComponentHandle genericHandle;
      } caster;
      Animation::PoseIndex poseHandle = getPoseHandle(clientEntity);
      caster.directionHandle = Direction::create(poseHandle, simEntity, group);
      linkComponent(clientEntity, ComponentType::Direction, caster.genericHandle);
      return caster.directionHandle;
    }

    Interpolation::Handle getInterpolation(EntityHandle entity) {
      static_assert(sizeof(Interpolation::Handle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        Interpolation::Handle interpolationHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entity, ComponentType::Interpolation);
      return caster.interpolationHandle;
    }

    Animation::PoseIndex getPoseHandle(EntityHandle entity) {
      static_assert(sizeof(Animation::PoseIndex) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        Animation::PoseIndex poseHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entity, ComponentType::Pose);
      return caster.poseHandle;
    }

    Rendering::BoneMeshInstanceHandle getBoneMeshInstanceHandle(EntityHandle entity) {
      static_assert(sizeof(Rendering::BoneMeshInstanceHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        Animation::PoseIndex boneMeshInstanceHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entity, ComponentType::BoneMeshInstance);
      return caster.boneMeshInstanceHandle;
    }
  }
}
