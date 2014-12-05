#include "Rendering/Renderer.h"
#include "Animation/JointConfig.h"
#include "PlayerControl.h"
#include "Rendering/MeshInfo.h"
#include "Rendering/Shape.h"
#include "MainFlow/PlayState.h"

namespace MainFlow {
  PlayState::PlayState(Rendering::Renderer &renderer) :
  renderer(renderer) { }

  void PlayState::enter() {
    renderer.setPoses(animator.getWorldPoses());
    renderer.setDynamicTransforms(frameInterpolator.getTransforms());
    renderer.setStaticTransforms(physics.getStaticTransforms());

    uint8_t jointParentIndices[] = { 0, 1, 1, 0, 0 };

    float animationDurations[] = { 3.0f, 1.0f };
    uint8_t animationKeyCounts[] = { 2, 4 };

    float keyTimes[] = { 0, 1.5f, 0, 0.25f, 0.5f, 0.75f };

    Animation::JointConfig keyJointConfigs[] = {
      // idle standard
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },

      // idle deep breath
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, -0.05, 0, 1, 0, 0, 0 },
      { -0.05, 0, 0, 1, 0, 0, 0 },
      { 0.05, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },

      // run mid
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },

      // run left foot front
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, -0.1, 0, 1, 0, 0, 0 },
      { 0, 0, -0.2, 1, 0, 0, 0 },
      { 0, 0, 0.2, 1, 0, 0, 0 },
      { 0, 0, -0.2, 1, 0, 0, 0 },
      { 0, 0, 0.2, 1, 0, 0, 0 },

      // run mid
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0 },

      // run right foot front
      { 0, 0, 0, 1, 0, 0, 0 },
      { 0, -0.1, 0, 1, 0, 0, 0 },
      { 0, 0, 0.2, 1, 0, 0, 0 },
      { 0, 0, -0.2, 1, 0, 0, 0 },
      { 0, 0, 0.2, 1, 0, 0, 0 },
      { 0, 0, -0.2, 1, 0, 0, 0 }
    };

    uint8_t skeletonID = animator.createSkeleton(
      jointParentIndices,
      sizeof(jointParentIndices)/sizeof(uint8_t),
      animationDurations,
      animationKeyCounts,
      sizeof(animationDurations)/sizeof(float),
      keyTimes,
      keyJointConfigs
    );

    Rendering::BoneVertex vertices[] = {
      // body, front
      { { -0.5, 1.6, -0.5 }, 1 }, // the 1 is the joint number this vertex will follow
      { { 0.5, 1.6, -0.5 }, 1 },
      { { -0.5, 0.6, -0.5 }, 1 },
      { { 0.5, 0.6, -0.5 }, 1 },
      // body, back
      { { -0.5, 1.6, 0.5 }, 1 },
      { { 0.5, 1.6, 0.5 }, 1 },
      { { -0.5, 0.6, 0.5 }, 1 },
      { { 0.5, 0.6, 0.5 }, 1 },

      // left hand, front
      { { -1, 1.3, -0.2 }, 2 },
      { { -0.6, 1.3, -0.2 }, 2 },
      { { -1, 0.9, -0.2 }, 2 },
      { { -0.6, 0.9, -0.2 }, 2 },
      // left hand, back
      { { -1, 1.3, 0.2 }, 2 },
      { { -0.6, 1.3, 0.2 }, 2 },
      { { -1, 0.9, 0.2 }, 2 },
      { { -0.6, 0.9, 0.2 }, 2 },

      // right hand, front
      { { 1, 1.3, -0.2 }, 3 },
      { { 0.6, 1.3, -0.2 }, 3 },
      { { 1, 0.9, -0.2 }, 3 },
      { { 0.6, 0.9, -0.2 }, 3 },
      // right hand, back
      { { 1, 1.3, 0.2 }, 3 },
      { { 0.6, 1.3, 0.2 }, 3 },
      { { 1, 0.9, 0.2 }, 3 },
      { { 0.6, 0.9, 0.2 }, 3 },

      // left foot, front
      { { -0.5, 0.4, -0.2 }, 4 },
      { { -0.1, 0.4, -0.2 }, 4 },
      { { -0.5, 0, -0.2 }, 4 },
      { { -0.1, 0, -0.2 }, 4 },
      // left foot, back
      { { -0.5, 0.4, 0.2 }, 4 },
      { { -0.1, 0.4, 0.2 }, 4 },
      { { -0.5, 0, 0.2 }, 4 },
      { { -0.1, 0, 0.2 }, 4 },

      // right foot, front
      { { 0.5, 0.4, -0.2 }, 5 },
      { { 0.1, 0.4, -0.2 }, 5 },
      { { 0.5, 0, -0.2 }, 5 },
      { { 0.1, 0, -0.2 }, 5 },
      // right foot, back
      { { 0.5, 0.4, 0.2 }, 5 },
      { { 0.1, 0.4, 0.2 }, 5 },
      { { 0.5, 0, 0.2 }, 5 },
      { { 0.1, 0, 0.2 }, 5 },
    };

    uint16_t indices[] = {
      // body
      0, 2, 1, 1, 2, 3, // front
      1, 3, 7, 1, 7, 5, // right
      4, 7, 6, 4, 5, 7, // back
      0, 6, 2, 0, 4, 6, // right
      5, 0, 1, 5, 4, 0, // top
      2, 7, 3, 2, 6, 7,  // bottom

      // left hand
      8, 10, 9, 9, 10, 11, // front
      9, 11, 15, 9, 15, 13, // right
      12, 15, 14, 12, 13, 15, // back
      8, 14, 10, 8, 12, 14, // right
      13, 8, 9, 13, 12, 8, // top
      10, 15, 11, 10, 14, 15,  // bottom

      // right hand
      17, 18, 16, 19, 18, 17, // front
      23, 19, 17, 21, 23, 17, // right
      22, 23, 20, 23, 21, 20, // back
      18, 22, 16, 22, 20, 16, // right
      17, 16, 21, 16, 20, 21, // top
      19, 23, 18, 23, 22, 18,  // bottom

      // left foot
      24, 26, 25, 25, 26, 27, // front
      25, 27, 31, 25, 31, 29, // right
      28, 31, 30, 28, 29, 31, // back
      24, 30, 26, 24, 28, 30, // right
      29, 24, 25, 29, 28, 24, // top
      26, 31, 27, 26, 30, 31,  // bottom

      // right foot
      33, 34, 32, 35, 34, 33, // front
      39, 35, 33, 37, 39, 33, // right
      38, 39, 36, 39, 37, 36, // back
      34, 38, 32, 38, 36, 32, // right
      33, 32, 37, 32, 36, 37, // top
      35, 39, 34, 39, 38, 34,  // bottom
    };

    Rendering::BoneMeshIndex meshIndex = renderer.createBoneMesh(
      vertices,
      sizeof(vertices)/sizeof(Rendering::BoneVertex),
      indices,
      sizeof(indices)/sizeof(uint16_t)
    );

    setupPlayer(meshIndex, skeletonID);
    setupMonster(meshIndex, skeletonID, 2, 2);
    setupMonster(meshIndex, skeletonID, 2, -2);
    setupMonster(meshIndex, skeletonID, -2, 2);
    setupMonster(meshIndex, skeletonID, -2, -2);

    setupGround();

    setupRock();

    renderer.setLightDirection(Quanta::Vector3(-2, -3, 1).getNormalized());

    Quanta::Transform& camera = renderer.getCameraTransform();
    camera.position[2] = -12;
    camera.position[1] = 6;
    camera.rotateX(0.5);
  }

  void PlayState::setupGround() {
    Rendering::StaticVertex vertices[] = {
      { { -5, 0, 5 } },
      { { 5, 0, 5 } },
      { { -5, 0, -5 } },
      { { 5, 0, -5 } },
      { { -5, -0.2, -5 } },
      { { 5, -0.2, -5 } }
    };

    uint16_t indices[] = {
      0, 2, 1, 1, 2, 3, // top
      2, 4, 3, 3, 4, 5
    };

    // color, offset, count
    Rendering::Shape shapes[] = {
      { { 0.64, 0.83, 0.33 }, 0, 4 },
    };

    Rendering::MeshInfo info;
    info.vertexCount = sizeof(vertices)/sizeof(Rendering::BoneVertex);
    info.indexCount = sizeof(indices)/sizeof(uint16_t);
    info.shapeCount = 1;

    Rendering::StaticMeshIndex mesh = renderer.createStaticMesh(info, vertices, indices, shapes);

    Physics::StaticBodyIndex body = physics.createStaticBody();
    renderer.createStaticMeshInstance(mesh, body);
  }

  void PlayState::setupPlayer(Rendering::BoneMeshIndex mesh, uint8_t skeletonID) {
    Animation::PoseIndex pose = animator.createPose(skeletonID);

    playerBody = physics.createDynamicBody();
    physics.createDynamicSphereCollider(playerBody, 0.5);

    uint8_t interpolationTransformID = frameInterpolator.createInterpolation(playerBody);
    frameInterpolator.initialize(physics.getDynamicPositions(), physics.getDynamicOrientations());

    airDrag.add(playerBody);

    renderer.createBoneMeshInstance(mesh, interpolationTransformID, pose);
  }

  void PlayState::setupRock() {
    Rendering::StaticVertex vertices[] = {
      { { -0.4, 1, -0.4 } },
      { { 0.4, 1, -0.4 } },
      { { -1, -1, -1 } },
      { { 1, -1, -1 } },
      { { -0.4, 1, 0.4 } },
      { { 0.4, 1, 0.4 } },
      { { -1, -1, 1 } },
      { { 1, -1, 1 } }
    };

    uint16_t indices[] = {
      0, 2, 1, 1, 2, 3, // front
      1, 3, 7, 1, 7, 5, // right
      4, 7, 6, 4, 5, 7, // back
      0, 6, 2, 0, 4, 6, // right
      2, 7, 3, 2, 6, 7,  // bottom
      5, 0, 1, 5, 4, 0 // top
    };

    Rendering::Shape shapes[] = {
      { { 0.5, 0.5, 0.5 }, 0, 10 },
      { { 0.7, 0.3, 0.3 }, 10, 2 }
    };

    Rendering::MeshInfo info;
    info.vertexCount = sizeof(vertices)/sizeof(Rendering::BoneVertex);
    info.indexCount = sizeof(indices)/sizeof(uint16_t);
    info.shapeCount = sizeof(shapes)/sizeof(Rendering::Shape);

    Rendering::StaticMeshIndex mesh = renderer.createStaticMesh(info, vertices, indices, shapes);

    Physics::StaticBodyIndex bodyIndex = physics.createStaticBody();
    Physics::StaticBody body = physics.getStaticBody(bodyIndex);
    (*body.position)[0] = 2;

    renderer.createStaticMeshInstance(mesh, bodyIndex);
  }

  void PlayState::setupMonster(Rendering::BoneMeshIndex mesh, uint8_t skeletonID, float x, float z) {
    Animation::PoseIndex pose = animator.createPose(skeletonID);

    Physics::DynamicBodyIndex bodyIndex = physics.createDynamicBody();
    Physics::DynamicBody body = physics.getDynamicBody(bodyIndex);
    (*body.position)[0] = x;
    (*body.position)[2] = z;
    physics.createDynamicSphereCollider(bodyIndex, 0.5);

    uint8_t interpolationTransformID = frameInterpolator.createInterpolation(bodyIndex);
    frameInterpolator.initialize(physics.getDynamicPositions(), physics.getDynamicOrientations());

    airDrag.add(bodyIndex);

    renderer.createBoneMeshInstance(mesh, interpolationTransformID, pose);
  }

  void PlayState::update(double timeDelta) {
    stepTimeBank += timeDelta;
    if(stepTimeBank >= Physics::Config::stepDuration) {
      Physics::DynamicBody body = physics.getDynamicBody(playerBody);
      do {
        playerControlUpdateForce(body);
        airDrag.update(physics.getDynamicVelocities(), physics.getDynamicForces());
        physics.simulate();
        stepTimeBank -= Physics::Config::stepDuration;
      } while(stepTimeBank >= Physics::Config::stepDuration);
      playerControlReact(body, animator);
      frameInterpolator.reload(physics.getDynamicPositions(), physics.getDynamicOrientations());
    }
    frameInterpolator.interpolate(stepTimeBank/Physics::Config::stepDuration);
    animator.update(timeDelta);
  }

  State* PlayState::checkTransition() {
    return nullptr;
  }
}
