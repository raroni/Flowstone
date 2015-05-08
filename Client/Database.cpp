#include "Database/EntityManager.h"
#include "Rendering/Renderer.h"
#include "Database/ComponentManager.h"
#include "Animation/Animator.h"
#include "Client/Interpolation.h"
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

    Animation::PoseHandle createPose(EntityHandle entity, Animation::SkeletonHandle skeleton) {
      union {
        Animation::PoseHandle poseHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.poseHandle = Animation::Animator::createPose(skeleton);
      linkComponent(entity, ComponentType::Pose, caster.genericHandle);
      return caster.poseHandle;
    }

    InterpolationHandle createInterpolation(::Database::EntityHandle entity, Physics::BodyHandle physicsBody) {
      union {
        InterpolationHandle interpolationHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.interpolationHandle = Interpolation::createInterpolation(physicsBody);
      linkComponent(entity, ComponentType::Interpolation, caster.genericHandle);
      return caster.interpolationHandle;
    }

    Rendering::BoneMeshDrawHandle createBoneMeshDraw(EntityHandle entity, Rendering::BoneMeshIndex mesh) {
      union {
        Rendering::BoneMeshDrawHandle drawHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.drawHandle = Rendering::Renderer::createBoneMeshDraw(mesh);
      linkComponent(entity, ComponentType::BoneMeshDraw, caster.genericHandle);
      return caster.drawHandle;
    }

    Rendering::StaticMeshDrawHandle createStaticMeshDraw(::Database::EntityHandle entity, Rendering::StaticMeshIndex mesh) {
      union {
        Rendering::StaticMeshDrawHandle drawHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.drawHandle = Rendering::Renderer::createStaticMeshDraw(mesh);
      linkComponent(entity, ComponentType::StaticMeshDraw, caster.genericHandle);
      return caster.drawHandle;
    }

    BoneMeshRenderFeedHandle createRenderFeed(EntityHandle entity) {
      assert(hasComponent(entity, ComponentType::Interpolation));
      assert(hasComponent(entity, ComponentType::Pose));
      assert(hasComponent(entity, ComponentType::BoneMeshDraw));

      union {
        BoneMeshRenderFeedHandle feedHandle;
        ComponentHandle genericHandle;
      } caster;
      InterpolationHandle interpolationHandle = getInterpolation(entity);
      Animation::PoseHandle poseHandle = getPoseHandle(entity);
      Rendering::BoneMeshDrawHandle boneMeshDrawHandle = getBoneMeshDrawHandle(entity);
      caster.feedHandle = RenderFeed::createBoneMeshFeed(interpolationHandle, poseHandle, boneMeshDrawHandle);
      linkComponent(entity, ComponentType::RenderFeed, caster.genericHandle);
      return caster.feedHandle;
    }

    DirectionHandle createDirection(EntityHandle clientEntity, EntityHandle simEntity, DirectionGroupHandle group) {
      union {
        DirectionHandle directionHandle;
        ComponentHandle genericHandle;
      } caster;
      Animation::PoseHandle poseHandle = getPoseHandle(clientEntity);
      caster.directionHandle = Direction::create(poseHandle, simEntity, group);
      linkComponent(clientEntity, ComponentType::Direction, caster.genericHandle);
      return caster.directionHandle;
    }

    InterpolationHandle getInterpolation(EntityHandle entity) {
      static_assert(sizeof(InterpolationHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        InterpolationHandle interpolationHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entity, ComponentType::Interpolation);
      return caster.interpolationHandle;
    }

    Animation::PoseHandle getPoseHandle(EntityHandle entity) {
      static_assert(sizeof(Animation::PoseHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        Animation::PoseHandle poseHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entity, ComponentType::Pose);
      return caster.poseHandle;
    }

    Rendering::BoneMeshDrawHandle getBoneMeshDrawHandle(EntityHandle entity) {
      static_assert(sizeof(Rendering::BoneMeshDrawHandle) == sizeof(ComponentHandle), "Handle size must be the same.");
      union {
        Animation::PoseHandle boneMeshDrawHandle;
        ComponentHandle genericHandle;
      } caster;
      caster.genericHandle = getComponent(entity, ComponentType::BoneMeshDraw);
      return caster.boneMeshDrawHandle;
    }
  }
}
