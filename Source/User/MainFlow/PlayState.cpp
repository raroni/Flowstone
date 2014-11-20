#include "Rendering2/Renderer.h"
#include "Animation/JointConfig.h"
#include "PlayerControl.h"
#include "MainFlow/PlayState.h"

namespace MainFlow {
  PlayState::PlayState(Rendering2::Renderer &renderer) :
  renderer(renderer) { }

  void PlayState::enter() {
    renderer.setPoses(animator.getWorldPoses());
    renderer.setTransforms(frameInterpolator.getTransforms());

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

    Rendering2::AnimatedVertex vertices[] = {
      // body, front
      { -0.5, 0.5, -0.5, 1 }, // the 1 is the joint number this vertex will follow
      { 0.5, 0.5, -0.5, 1 },
      { -0.5, -0.5, -0.5, 1 },
      { 0.5, -0.5, -0.5, 1 },
      // body, back
      { -0.5, 0.5, 0.5, 1 },
      { 0.5, 0.5, 0.5, 1 },
      { -0.5, -0.5, 0.5, 1 },
      { 0.5, -0.5, 0.5, 1 },

      // left hand, front
      { -1, 0.2, -0.2, 2 },
      { -0.6, 0.2, -0.2, 2 },
      { -1, -0.2, -0.2, 2 },
      { -0.6, -0.2, -0.2, 2 },
      // left hand, back
      { -1, 0.2, 0.2, 2 },
      { -0.6, 0.2, 0.2, 2 },
      { -1, -0.2, 0.2, 2 },
      { -0.6, -0.2, 0.2, 2 },

      // right hand, front
      { 1, 0.2, -0.2, 3 },
      { 0.6, 0.2, -0.2, 3 },
      { 1, -0.2, -0.2, 3 },
      { 0.6, -0.2, -0.2, 3 },
      // right hand, back
      { 1, 0.2, 0.2, 3 },
      { 0.6, 0.2, 0.2, 3 },
      { 1, -0.2, 0.2, 3 },
      { 0.6, -0.2, 0.2, 3 },

      // left foot, front
      { -0.5, -0.7, -0.2, 4 },
      { -0.1, -0.7, -0.2, 4 },
      { -0.5, -1.1, -0.2, 4 },
      { -0.1, -1.1, -0.2, 4 },
      // left foot, back
      { -0.5, -0.7, 0.2, 4 },
      { -0.1, -0.7, 0.2, 4 },
      { -0.5, -1.1, 0.2, 4 },
      { -0.1, -1.1, 0.2, 4 },

      // right foot, front
      { 0.5, -0.7, -0.2, 5 },
      { 0.1, -0.7, -0.2, 5 },
      { 0.5, -1.1, -0.2, 5 },
      { 0.1, -1.1, -0.2, 5 },
      // right foot, back
      { 0.5, -0.7, 0.2, 5 },
      { 0.1, -0.7, 0.2, 5 },
      { 0.5, -1.1, 0.2, 5 },
      { 0.1, -1.1, 0.2, 5 },
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
      16, 18, 17, 17, 18, 19, // front
      17, 19, 23, 17, 23, 21, // right
      20, 23, 22, 20, 21, 23, // back
      16, 22, 18, 16, 20, 22, // right
      21, 16, 17, 21, 20, 16, // top
      18, 23, 19, 18, 22, 23,  // bottom

      // left foot
      24, 26, 25, 25, 26, 27, // front
      25, 27, 31, 25, 31, 29, // right
      28, 31, 30, 28, 29, 31, // back
      24, 30, 26, 24, 28, 30, // right
      29, 24, 25, 29, 28, 24, // top
      26, 31, 27, 26, 30, 31,  // bottom

      // right foot
      32, 34, 33, 33, 34, 35, // front
      33, 35, 39, 33, 39, 37, // right
      36, 39, 38, 36, 37, 39, // back
      32, 38, 34, 32, 36, 38, // right
      37, 32, 33, 37, 36, 32, // top
      34, 39, 35, 34, 38, 39,  // bottom
    };

    Rendering2::AnimatedMeshIndex meshIndex = renderer.createAnimatedMesh(
      vertices,
      sizeof(vertices)/sizeof(Rendering2::AnimatedVertex),
      indices,
      sizeof(indices)/sizeof(uint16_t)
    );

    animator.createSkeletonInstance(skeletonID);

    playerBodyIndex = physics.createDynamicBody();
    physics.createDynamicSphereCollider(playerBodyIndex, 0.5);

    uint8_t interpolationTransformID = frameInterpolator.createInterpolation(playerBodyIndex);

    airDrag.add(playerBodyIndex);

    renderer.createAnimatedMeshInstance(meshIndex, interpolationTransformID);

    renderer.cameraTransform.position[2] = -12;
    renderer.cameraTransform.position[1] = 6;
    renderer.cameraTransform.rotateX(0.5);
  }

  void PlayState::update(double timeDelta) {
    stepTimeBank += timeDelta;
    if(stepTimeBank >= Physics::Config::stepDuration) {
      Physics::DynamicBody body = physics.getDynamicBody(playerBodyIndex);
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

    /*
    Rendering::WorldRenderer &worldRenderer = renderer.getWorldRenderer();
    Rendering::Component *component = worldRenderer.getComponent(0);
    component->transform.position[0] += deltaTime;
    component->transform.position[1] += deltaTime*0.5;
    //worldRenderer.cameraTransform.position[0] += deltaTime;
    */

    /*
    Rendering::WorldRenderer &worldRenderer = renderer.getWorldRenderer();
    Rendering::AnimatedMeshInstance *instance = worldRenderer.getAnimatedMeshInstance(0);
    instance->transform.rotateY(deltaTime*0.1);
    */
  }

  State* PlayState::checkTransition() {
    return nullptr;
  }
}
