#ifndef CLIENT_DATABASE_H
#define CLIENT_DATABASE_H

#include "Physics/BodyHandle.h"
#include "Database/EntityHandle.h"
#include "Rendering/BoneMeshDrawHandle.h"
#include "Rendering/BoneMeshIndex.h"
#include "Animation/PoseHandle.h"
#include "Client/BoneMeshRenderFeedHandle.h"
#include "Client/InterpolationHandle.h"
#include "Client/Direction/DirectionInstanceHandle.h"
#include "Client/Direction/DirectionGroupIndex.h"
#include "Animation/SkeletonHandle.h"

namespace Client {
  namespace Database {
    ::Database::EntityHandle createEntity();
    Animation::PoseHandle createPose(::Database::EntityHandle entity, Animation::SkeletonHandle skeletonHandle);
    InterpolationHandle createInterpolation(::Database::EntityHandle entity, Physics::BodyHandle physicsBody);
    Rendering::BoneMeshDrawHandle createBoneMeshDraw(::Database::EntityHandle entity, Rendering::BoneMeshIndex mesh);
    Rendering::StaticMeshDrawHandle createStaticMeshDraw(::Database::EntityHandle entity, Rendering::StaticMeshIndex mesh);
    DirectionInstanceHandle createDirection(::Database::EntityHandle clientEntity, DirectionGroupIndex group, ::Database::EntityHandle simEntity);
    BoneMeshRenderFeedHandle createRenderFeed(::Database::EntityHandle entity);
    InterpolationHandle getInterpolation(::Database::EntityHandle entity);
    Animation::PoseHandle getPoseHandle(::Database::EntityHandle entity);
    Rendering::BoneMeshDrawHandle getBoneMeshDrawHandle(::Database::EntityHandle entity);
  }
}

#endif
