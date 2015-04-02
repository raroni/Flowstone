#include "Quanta/Geometry/Transformer.h"
#include "Rendering/Renderer.h"
#include "Rendering/PointLightHandle.h"
#include "Rendering/MeshInfo.h"
#include "Rendering/Shape.h"
#include "Animation/JointConfig.h"
#include "Client/PlayerControl.h"
#include "Client/MainFlow/PlayState.h"

namespace MainFlow {
  PlayState::PlayState(Rendering::Renderer &renderer) :
  renderer(renderer),
  rendererFeeder(physics, interpolater, animator, renderer),
  torches(renderer) { }

  void PlayState::enter() {
    torches.initialize();

    uint8_t jointParentIndices[] = { 0, 1, 1, 0, 0 };

    float animationDurations[] = { 3.0f, 1.0f };
    uint8_t animationKeyCounts[] = { 2, 4 };

    float keyTimes[] = { 0, 1.5f, 0, 0.25f, 0.5f, 0.75f };

    updateAtmosphereColor();
    updateLightDirection();

    Quanta::Vector3 secondaryLightDirection = Quanta::Vector3(2, 1, 5).getNormalized()*-1;
    renderer.setSecondaryLightDirection(secondaryLightDirection);

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
      { { -0.25, 0.8, -0.25 }, 1 }, // the 1 is the joint number this vertex will follow
      { { 0.25, 0.8, -0.25 }, 1 },
      { { -0.25, 0.3, -0.25 }, 1 },
      { { 0.25, 0.3, -0.25 }, 1 },
      // body, back
      { { -0.25, 0.8, 0.25 }, 1 },
      { { 0.25, 0.8, 0.25 }, 1 },
      { { -0.25, 0.3, 0.25 }, 1 },
      { { 0.25, 0.3, 0.25 }, 1 },

      // left hand, front
      { { -0.5, 0.65, -0.1 }, 2 },
      { { -0.3, 0.65, -0.1 }, 2 },
      { { -0.5, 0.45, -0.1 }, 2 },
      { { -0.3, 0.45, -0.1 }, 2 },
      // left hand, back
      { { -0.5, 0.65, 0.1 }, 2 },
      { { -0.3, 0.65, 0.1 }, 2 },
      { { -0.5, 0.45, 0.1 }, 2 },
      { { -0.3, 0.45, 0.1 }, 2 },

      // right hand, front
      { { 0.5, 0.65, -0.1 }, 3 },
      { { 0.3, 0.65, -0.1 }, 3 },
      { { 0.5, 0.45, -0.1 }, 3 },
      { { 0.3, 0.45, -0.1 }, 3 },
      // right hand, back
      { { 0.5, 0.65, 0.1 }, 3 },
      { { 0.3, 0.65, 0.1 }, 3 },
      { { 0.5, 0.45, 0.1 }, 3 },
      { { 0.3, 0.45, 0.1 }, 3 },

      // left foot, front
      { { -0.25, 0.2, -0.1}, 4 },
      { { -0.1, 0.2, -0.1}, 4 },
      { { -0.25, 0, -0.1}, 4 },
      { { -0.1, 0, -0.1}, 4 },
      // left foot, back
      { { -0.25, 0.2, 0.1}, 4 },
      { { -0.1, 0.2, 0.1}, 4 },
      { { -0.25, 0, 0.1}, 4 },
      { { -0.1, 0, 0.1}, 4 },

      // right foot, front
      { { 0.25, 0.2, -0.1}, 5 },
      { { 0.1, 0.2, -0.1}, 5 },
      { { 0.25, 0, -0.1}, 5 },
      { { 0.1, 0, -0.1}, 5 },
      // right foot, back
      { { 0.25, 0.2, 0.1}, 5 },
      { { 0.1, 0.2, 0.1}, 5 },
      { { 0.25, 0, 0.1}, 5 },
      { { 0.1, 0, 0.1}, 5 }
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
    setupMonster(meshIndex, skeletonID, 2, 1);
    setupMonster(meshIndex, skeletonID, 1, -1);
    setupMonster(meshIndex, skeletonID, -1, -1);

    configureRedTree();
    configureGreenTree();

    setupTree(-3, 0, greenTreeMesh);
    setupTree(-3, -1, greenTreeMesh);
    setupTree(-3, -2, redTreeMesh);

    setupTree(-2, 1, redTreeMesh);
    setupTree(-1, 1, redTreeMesh);
    setupTree(0, 1, redTreeMesh);

    setupTree(-3, 3, greenTreeMesh);
    setupTree(-2, 3, redTreeMesh);
    setupTree(0, 3, redTreeMesh);
    setupTree(1, 3, greenTreeMesh);
    setupTree(2, 3, greenTreeMesh);

    setupRock();
    setupGround();
    setupBox();

    torches.create(1, 2);
    torches.create(1, 0);
    torches.create(1, -2);
    torches.create(-1, 3);
    torches.create(-4, 2);

    Quanta::Transform& camera = renderer.getCameraTransform();
    camera.position[2] = -3.75;
    camera.position[1] = 6;
    camera.rotateX(1);
  }

  void PlayState::configureGreenTree() {
    float trunkWidth = 0.25;
    float trunkHeight = 0.6;
    float crownWidth = 0.75;
    float crownHeight = 0.5;

    float halfTrunkWidth = trunkWidth*0.5;
    float halfCrownWidth = crownWidth*0.5;

    Rendering::StaticVertex vertices[] = {
      // trunk
      { { -halfTrunkWidth, trunkHeight, -halfTrunkWidth } },
      { { halfTrunkWidth, trunkHeight, -halfTrunkWidth } },
      { { -halfTrunkWidth, 0, -halfTrunkWidth } },
      { { halfTrunkWidth, 0, -halfTrunkWidth } },
      { { -halfTrunkWidth, trunkHeight, halfTrunkWidth } },
      { { halfTrunkWidth, trunkHeight, halfTrunkWidth } },
      { { -halfTrunkWidth, 0, halfTrunkWidth } },
      { { halfTrunkWidth, 0, halfTrunkWidth } },

      // crown
      { { -halfCrownWidth, trunkHeight+crownHeight, -halfCrownWidth } },
      { { halfCrownWidth, trunkHeight+crownHeight, -halfCrownWidth } },
      { { -halfCrownWidth, trunkHeight, -halfCrownWidth } },
      { { halfCrownWidth, trunkHeight, -halfCrownWidth } },
      { { -halfCrownWidth, trunkHeight+crownHeight, halfCrownWidth } },
      { { halfCrownWidth, trunkHeight+crownHeight, halfCrownWidth } },
      { { -halfCrownWidth, trunkHeight, halfCrownWidth } },
      { { halfCrownWidth, trunkHeight, halfCrownWidth } }
    };

    uint16_t indices[] = {
      // trunk
      0, 2, 1, 1, 2, 3,
      1, 3, 7, 1, 7, 5,
      4, 7, 6, 4, 5, 7, // back
      0, 6, 2, 0, 4, 6, // right
      2, 7, 3, 2, 6, 7,  // bottom
      5, 0, 1, 5, 4, 0, // top

      // crown
      8, 10, 9, 9, 10, 11,
      9, 11, 15, 9, 15, 13,
      12, 15, 14, 12, 13, 15,
      8, 14, 10, 8, 12, 14,
      10, 15, 11, 10, 14, 15,
      13, 8, 9, 13, 12, 8,
    };

    Rendering::Shape shapes[] = {
      { { 0.56, 0.36, 0.20 }, 0.0, 0, 12 },
      { { 0.41, 0.61, 0.21 }, 0.0, 12, 12 }
    };

    Rendering::MeshInfo info;
    info.vertexCount = sizeof(vertices)/sizeof(Rendering::StaticVertex);
    info.indexCount = sizeof(indices)/sizeof(uint16_t);
    info.shapeCount = sizeof(shapes)/sizeof(Rendering::Shape);

    greenTreeMesh = renderer.createStaticMesh(info, vertices, indices, shapes);
  }

  void PlayState::configureRedTree() {
    float trunkWidth = 0.35;
    float trunkHeight = 0.5;
    float crownWidth = 0.6;
    float crownHeight = 0.75;

    float halfTrunkWidth = trunkWidth*0.5;
    float halfCrownWidth = crownWidth*0.5;

    Rendering::StaticVertex vertices[] = {
      // trunk
      { { -halfTrunkWidth, trunkHeight, -halfTrunkWidth } },
      { { halfTrunkWidth, trunkHeight, -halfTrunkWidth } },
      { { -halfTrunkWidth, 0, -halfTrunkWidth } },
      { { halfTrunkWidth, 0, -halfTrunkWidth } },
      { { -halfTrunkWidth, trunkHeight, halfTrunkWidth } },
      { { halfTrunkWidth, trunkHeight, halfTrunkWidth } },
      { { -halfTrunkWidth, 0, halfTrunkWidth } },
      { { halfTrunkWidth, 0, halfTrunkWidth } },

      // crown
      { { -halfCrownWidth, trunkHeight+crownHeight, -halfCrownWidth } },
      { { halfCrownWidth, trunkHeight+crownHeight, -halfCrownWidth } },
      { { -halfCrownWidth, trunkHeight, -halfCrownWidth } },
      { { halfCrownWidth, trunkHeight, -halfCrownWidth } },
      { { -halfCrownWidth, trunkHeight+crownHeight, halfCrownWidth } },
      { { halfCrownWidth, trunkHeight+crownHeight, halfCrownWidth } },
      { { -halfCrownWidth, trunkHeight, halfCrownWidth } },
      { { halfCrownWidth, trunkHeight, halfCrownWidth } }
    };

    uint16_t indices[] = {
      // trunk
      0, 2, 1, 1, 2, 3,
      1, 3, 7, 1, 7, 5,
      4, 7, 6, 4, 5, 7, // back
      0, 6, 2, 0, 4, 6, // right
      2, 7, 3, 2, 6, 7,  // bottom
      5, 0, 1, 5, 4, 0, // top

      // crown
      8, 10, 9, 9, 10, 11,
      9, 11, 15, 9, 15, 13,
      12, 15, 14, 12, 13, 15,
      8, 14, 10, 8, 12, 14,
      10, 15, 11, 10, 14, 15,
      13, 8, 9, 13, 12, 8,
    };

    Rendering::Shape shapes[] = {
      { { 0.56, 0.36, 0.20 }, 0.0, 0, 12 },
      { { 1, 0.36, 0.20 }, 0.0, 12, 12 }
    };

    Rendering::MeshInfo info;
    info.vertexCount = sizeof(vertices)/sizeof(Rendering::StaticVertex);
    info.indexCount = sizeof(indices)/sizeof(uint16_t);
    info.shapeCount = sizeof(shapes)/sizeof(Rendering::Shape);

    redTreeMesh = renderer.createStaticMesh(info, vertices, indices, shapes);
  }

  void PlayState::setupTree(float x, float z, Rendering::StaticMeshIndex mesh) {
    Physics::StaticBodyIndex bodyIndex = physics.createStaticBody();
    physics.createStaticSphereCollider(bodyIndex, 0.4);
    Physics::StaticBody body = physics.getStaticBody(bodyIndex);
    (*body.position)[0] = x;
    (*body.position)[2] = z;

    Rendering::StaticMeshInstanceHandle meshInstance = renderer.createStaticMeshInstance(mesh);
    rendererFeeder.bindStaticStatic(bodyIndex, meshInstance);
  }

  void PlayState::setupGround() {
    Rendering::StaticVertex vertices[] = {
      { { -15, 0, -15 } },
      { { 15, 0, -15 } },
      { { -15, -0.5, -15 } },
      { { 15, -0.5, -15 } },
      { { -15, 0, 15 } },
      { { 15, 0, 15 } },
      { { -15, -0.5, 15 } },
      { { 15, -0.5, 15 } }
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
      { { 0.64, 0.83, 0.33 }, 0.0, 0, 12 }
    };

    Rendering::MeshInfo info;
    info.vertexCount = sizeof(vertices)/sizeof(Rendering::StaticVertex);
    info.indexCount = sizeof(indices)/sizeof(uint16_t);
    info.shapeCount = 1;

    Rendering::StaticMeshIndex mesh = renderer.createStaticMesh(info, vertices, indices, shapes);

    Physics::StaticBodyIndex body = physics.createStaticBody();
    Rendering::StaticMeshInstanceHandle meshInstance = renderer.createStaticMeshInstance(mesh);

    rendererFeeder.bindStaticStatic(body, meshInstance);
  }

  void PlayState::setupPlayer(Rendering::BoneMeshIndex mesh, uint8_t skeletonID) {
    Animation::PoseIndex pose = animator.createPose(skeletonID);

    playerBody = physics.createDynamicBody();
    physics.createDynamicSphereCollider(playerBody, 0.25);

    Interpolation::Index interpolation = interpolater.createInterpolation(playerBody);
    interpolater.initialize(physics.getDynamicPositions(), physics.getDynamicOrientations());

    airDrag.add(playerBody);

    Rendering::BoneMeshInstanceHandle meshInstance = renderer.createBoneMeshInstance(mesh);

    rendererFeeder.setupBoneMesh(interpolation, pose, meshInstance);
  }

  void PlayState::setupBox() {
    Rendering::StaticVertex vertices[] = {
      { { -0.5, 0.5, -0.5 } },
      { { 0.5, 0.5, -0.5 } },
      { { -0.5, -0.5, -0.5 } },
      { { 0.5, -0.5, -0.5 } },
      { { -0.5, 0.5, 0.5 } },
      { { 0.5, 0.5, 0.5 } },
      { { -0.5, -0.5, 0.5 } },
      { { 0.5, -0.5, 0.5 } }
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
      { { 0.5, 0.5, 0.5 }, 0.0, 0, 12 }
    };

    Rendering::MeshInfo info;
    info.vertexCount = sizeof(vertices)/sizeof(Rendering::BoneVertex);
    info.indexCount = sizeof(indices)/sizeof(uint16_t);
    info.shapeCount = sizeof(shapes)/sizeof(Rendering::Shape);

    Rendering::StaticMeshIndex mesh = renderer.createStaticMesh(info, vertices, indices, shapes);

    Physics::StaticBodyIndex bodyIndex = physics.createStaticBody();
    physics.createStaticSphereCollider(bodyIndex, 0.5);
    Physics::StaticBody body = physics.getStaticBody(bodyIndex);
    (*body.position)[0] = 4;
    Rendering::StaticMeshInstanceHandle meshInstance = renderer.createStaticMeshInstance(mesh);
    rendererFeeder.bindStaticStatic(bodyIndex, meshInstance);
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
      { { 0.5, 0.5, 0.5 }, 0.0, 0, 10 },
      { { 0.3, 0.3, 0.3 }, 0.0, 10, 2 }
    };

    Rendering::MeshInfo info;
    info.vertexCount = sizeof(vertices)/sizeof(Rendering::BoneVertex);
    info.indexCount = sizeof(indices)/sizeof(uint16_t);
    info.shapeCount = sizeof(shapes)/sizeof(Rendering::Shape);

    Rendering::StaticMeshIndex mesh = renderer.createStaticMesh(info, vertices, indices, shapes);

    Physics::StaticBodyIndex bodyIndex = physics.createStaticBody();
    physics.createStaticSphereCollider(bodyIndex, 0.8);
    Physics::StaticBody body = physics.getStaticBody(bodyIndex);
    (*body.position)[0] = 2;
    (*body.position)[2] = 2;

    Rendering::StaticMeshInstanceHandle meshInstance = renderer.createStaticMeshInstance(mesh);

    rendererFeeder.bindStaticStatic(bodyIndex, meshInstance);
  }

  void PlayState::setupMonster(Rendering::BoneMeshIndex mesh, uint8_t skeletonID, float x, float z) {
    Animation::PoseIndex pose = animator.createPose(skeletonID);

    Physics::DynamicBodyIndex bodyIndex = physics.createDynamicBody();
    Physics::DynamicBody body = physics.getDynamicBody(bodyIndex);
    (*body.position)[0] = x;
    (*body.position)[2] = z;
    physics.createDynamicSphereCollider(bodyIndex, 0.25);

    uint8_t interpolationTransformID = interpolater.createInterpolation(bodyIndex);
    interpolater.initialize(physics.getDynamicPositions(), physics.getDynamicOrientations());

    airDrag.add(bodyIndex);

    Rendering::BoneMeshInstanceHandle meshInstance = renderer.createBoneMeshInstance(mesh);

    rendererFeeder.setupBoneMesh(interpolationTransformID, pose, meshInstance);
  }

  void PlayState::update(double timeDelta, const Keyboard &keyboard) {
    timeOfDay += timeDelta*0.03;
    timeOfDay = fmod(timeOfDay, 1.0);

    stepTimeBank += timeDelta;
    if(stepTimeBank >= Physics::Config::stepDuration) {
      Physics::DynamicBody body = physics.getDynamicBody(playerBody);
      do {
        playerControlUpdateForce(body, keyboard);
        airDrag.update(physics.getDynamicVelocities(), physics.getDynamicForces());
        physics.simulate();
        stepTimeBank -= Physics::Config::stepDuration;
      } while(stepTimeBank >= Physics::Config::stepDuration);
      playerControlReact(body, animator);
      interpolater.reload(physics.getDynamicPositions(), physics.getDynamicOrientations());
    }
    interpolater.interpolate(stepTimeBank/Physics::Config::stepDuration);
    updateAtmosphereColor();
    updateLightDirection();
    rendererFeeder.update();
    animator.update(timeDelta);
  }

  State* PlayState::checkTransition() {
    return nullptr;
  }

  void PlayState::updateAtmosphereColor() {
    renderer.setPrimaryLightColor(atmosphereColor.get(timeOfDay));
  }

  void PlayState::updateLightDirection() {
    float offset = 0.07;
    if(timeOfDay >= 0.25 && timeOfDay < 0.75) {
      float progress = (timeOfDay-0.25)*2;
      float angle = M_PI*-offset + M_PI*(1+offset*2)*progress;

      Quanta::Vector3 axis(0, 0, -1);
      Quanta::Quaternion rotation = Quanta::TransformFactory3D::rotation(axis, angle);
      Quanta::Vector3 sunrise(-1, 0, -0.5);
      Quanta::Vector3 sunPosition = Quanta::Transformer::createRotatedVector3(sunrise, rotation);
      renderer.setPrimaryLightDirection(sunPosition*-1);
    } else {
      float progress;
      if(timeOfDay < 0.5) {
        progress = 0.5+timeOfDay*2;
      } else {
        progress = (timeOfDay-0.5)*2-0.5;
      }
      float angle = M_PI*-offset + M_PI*(1+offset*2)*progress;

      Quanta::Vector3 axis(0, 0, -1);
      Quanta::Quaternion rotation = Quanta::TransformFactory3D::rotation(axis, angle);
      Quanta::Vector3 sunrise(-1, 0, -0.5);
      Quanta::Vector3 sunPosition = Quanta::Transformer::createRotatedVector3(sunrise, rotation);
      renderer.setPrimaryLightDirection(sunPosition*-1);
    }
  }
}
