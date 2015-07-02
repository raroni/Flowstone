#include "Quanta/Geometry/Transformer.h"
#include "Quanta/Geometry/TransformFactory3D.h"
#include "Simulation/Control.h"
#include "Simulation/EntityList.h"
#include "Simulation/Database.h"
#include "Simulation/ComponentType.h"
#include "Simulation/PhysicsHack.h"
#include "Rendering/Renderer.h"
#include "Rendering/PointLightHandle.h"
#include "Rendering/MeshInfo.h"
#include "Rendering/Shape.h"
#include "Animation/JointConfig.h"
#include "Client/Direction.h"
#include "Client/RenderFeed.h"
#include "Client/CameraControl.h"
#include "Client/LocalSimulationDriver.h"
#include "Client/Database.h"
#include "Client/MainFlow/PlayState.h"

namespace Client {
  namespace MainFlow {
    using namespace ::Database;
    namespace SimDB = Simulation::Database;
    namespace SimControl = Simulation::Control;
    typedef Simulation::ComponentType SimComponentType;

    DirectionGroupIndex workerDirectionGroup;

    PlayState::PlayState(PlayMode playMode) :
    playMode(playMode) { }

    void PlayState::configureAnimation() {
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

      walkAnimationSkeleton = Animation::Animator::createSkeleton(
        jointParentIndices,
        sizeof(jointParentIndices)/sizeof(uint8_t),
        animationDurations,
        animationKeyCounts,
        sizeof(animationDurations)/sizeof(float),
        keyTimes,
        keyJointConfigs
      );
    }

    void PlayState::configureRenderer() {
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

      characterMesh = Rendering::Renderer::createBoneMesh(
        vertices,
        sizeof(vertices)/sizeof(Rendering::BoneVertex),
        indices,
        sizeof(indices)/sizeof(uint16_t)
      );
    }

    void PlayState::enter() {
      torches.initialize();

      updateAtmosphereColor();
      updateLightDirection();

      Quanta::Vector3 secondaryLightDirection = Quanta::Vector3(2, 1, 5).getNormalized()*-1;
      Rendering::Renderer::setSecondaryLightDirection(secondaryLightDirection);

      configureAnimation();
      configureRenderer();
      configureRedTree();
      configureGreenTree();

      /*
      setupRock();
      setupBox();

      torches.create(1, 2);
      torches.create(1, 0);
      torches.create(1, -2);
      torches.create(-1, 3);
      torches.create(-4, 2);
      */

      setupGround();

      workerDirectionGroup = Direction::createGroup(4);

      Quanta::Transform& camera = Rendering::Renderer::getCameraTransform();
      CameraControl::initialize(&camera);

      if(playMode == PlayMode::Local) {
        playerID = SimControl::createPlayer();
      }
      SimControl::start();

      Simulation::EntityList entities = SimDB::getEntityList();
      for(uint16_t i=0; i<entities.count; ++i) {
        EntityHandle entity = entities.values[i];

        if(SimDB::hasComponent(entity, SimComponentType::Resource)) {
          Physics::Body body = SimDB::getBody(entity);
          setupTree((*body.position)[0], (*body.position)[2], greenTreeMesh);
        }
        else if(SimDB::hasComponent(entity, SimComponentType::Worker)) {
          setupWorker(entity);
        }
      }

      Direction::prepare();
      Interpolation::prepare(Simulation::physicsEngine.getBodies());
    }

    void PlayState::exit() {
      SimControl::stop();
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

      greenTreeMesh = Rendering::Renderer::createStaticMesh(info, vertices, indices, shapes);
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

      redTreeMesh = Rendering::Renderer::createStaticMesh(info, vertices, indices, shapes);
    }

    void PlayState::setupTree(float x, float z, Rendering::StaticMeshIndex mesh) {
      EntityHandle tree = Database::createEntity();
      Rendering::StaticMeshDrawHandle draw = Database::createStaticMeshDraw(tree, mesh);
      Quanta::Matrix4 transform = Quanta::TransformFactory3D::translation({ x, 0, z });
      Rendering::Renderer::updateStaticMeshTransform(draw, transform);
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

      Rendering::StaticMeshIndex mesh = Rendering::Renderer::createStaticMesh(info, vertices, indices, shapes);
      Rendering::Renderer::createStaticMeshDraw(mesh);
    }

    void PlayState::setupWorker(EntityHandle simEntityHandle) {
      Physics::BodyHandle body = SimDB::getBodyHandle(simEntityHandle);
      EntityHandle clientEntityHandle = Database::createEntity();

      Database::createPose(clientEntityHandle, walkAnimationSkeleton);
      Database::createInterpolation(clientEntityHandle, body);
      Database::createBoneMeshDraw(clientEntityHandle, characterMesh);
      Database::createRenderFeed(clientEntityHandle);
      Database::createDirection(clientEntityHandle, workerDirectionGroup, simEntityHandle);
    }

    void PlayState::updateSimulation(double timeDelta) {
      if(playMode == PlayMode::Local) {
        LocalSimulationDriver::update(playerID, timeDelta, clientCommands, simulationCommands, simulationEvents);
      } else {
        // NetworkSimulationDriver::update(timeDelta, commandList);
        assert(false); // not implemented yet
      }
    }

    void PlayState::writeCommands() {
      if(SimControl::getFrame() == 0) {
        clientCommands.writeTestCommand(playerID);
      }
    }

    void PlayState::processSimulationEvents() {
      for(uint8_t i=0; i<simulationEvents.getCount(); ++i) {

      }
      simulationEvents.clear();
    }

    void PlayState::update(double timeDelta, const Keyboard &keyboard) {
      timeOfDay += timeDelta*0.03;
      timeOfDay = fmod(timeOfDay, 1.0);

      if(playerID != -1) {
        writeCommands();
      }
      updateSimulation(timeDelta);
      clientCommands.clear();
      Interpolation::reload(Simulation::physicsEngine.getBodies());
      Interpolation::interpolate(0.5); // todo: fix this

      processSimulationEvents();

      CameraControl::update(timeDelta, &keyboard, &Rendering::Renderer::getCameraTransform());
      updateAtmosphereColor();
      updateLightDirection();
      RenderFeed::update();
      Direction::update();
      Animation::Animator::update(timeDelta);
    }

    State* PlayState::checkTransition() {
      return nullptr;
    }

    void PlayState::updateAtmosphereColor() {
      Rendering::Renderer::setPrimaryLightColor(atmosphereColor.get(timeOfDay));
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
        Rendering::Renderer::setPrimaryLightDirection(sunPosition*-1);
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
        Rendering::Renderer::setPrimaryLightDirection(sunPosition*-1);
      }
    }
  }
}
