#ifndef CLIENT_DATABASE_H
#define CLIENT_DATABASE_H

#include "Physics/BodyHandle.h"
#include "Database/EntityHandle.h"
#include "Rendering/BoneMeshInstanceHandle.h"
#include "Rendering/BoneMeshIndex.h"
#include "Animation/PoseIndex.h"
#include "Client/Interpolation/Handle.h"
#include "Client/DirectionHandle.h"
#include "Client/DirectionGroupHandle.h"
#include "Animation/SkeletonHandle.h"

namespace Client {
  namespace Database {
    ::Database::EntityHandle createEntity();
    Animation::PoseIndex createPose(::Database::EntityHandle entity, Animation::SkeletonHandle skeletonHandle);
    Interpolation::Handle createInterpolation(::Database::EntityHandle entity, Physics::BodyHandle physicsBody);
    Rendering::BoneMeshInstanceHandle createBoneMeshInstance(::Database::EntityHandle entity, Rendering::BoneMeshIndex mesh);
    Rendering::StaticMeshInstanceHandle createStaticMeshInstance(::Database::EntityHandle entity, Rendering::StaticMeshIndex mesh);
    DirectionHandle createDirection(::Database::EntityHandle clientEntity, ::Database::EntityHandle simEntity, DirectionGroupHandle group);
    void createRenderFeed(::Database::EntityHandle entity);
    Interpolation::Handle getInterpolation(::Database::EntityHandle entity);
    Animation::PoseIndex getPoseHandle(::Database::EntityHandle entity);
    Rendering::BoneMeshInstanceHandle getBoneMeshInstanceHandle(::Database::EntityHandle entity);
  }
}

#endif
