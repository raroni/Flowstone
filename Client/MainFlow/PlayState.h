#ifndef CLIENT_MAIN_FLOW_PLAY_STATE_H
#define CLIENT_MAIN_FLOW_PLAY_STATE_H

#include <stddef.h>
#include "Physics/Engine.h"
#include "Animation/Animator.h"
#include "Simulation/CommandList.h"
#include "Simulation/PlayerID.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/StaticMeshIndex.h"
#include "Client/MainFlow/State.h"
#include "Client/CommandList.h"
#include "Client/AtmosphereColor.h"
#include "Client/TorchManager.h"
#include "Client/PlayMode.h"
#include "Client/RendererFeeder.h"
#include "Client/AirDrag.h"
#include "Client/Interpolation/Interpolater.h"

namespace Rendering {
  class Renderer;
}

namespace Client {
  namespace MainFlow {
    class Manager;

    class PlayState : public State {
    public:
      PlayState(Rendering::Renderer &renderer, PlayMode playMode);
      void enter();
      void update(double deltaTime, const Keyboard &keyboard);
      State* checkTransition();
    private:
      Simulation::PlayerID playerID = -1;
      PlayMode playMode;
      Animation::Animator animator;
      Physics::Engine physics;
      Rendering::Renderer &renderer;
      Interpolation::Interpolater interpolater;
      AirDrag airDrag;
      double stepTimeBank = 0;
      float timeOfDay = 0.3;
      Physics::DynamicBodyIndex playerBody;
      RendererFeeder rendererFeeder;
      AtmosphereColor atmosphereColor;
      Rendering::StaticMeshIndex greenTreeMesh;
      Rendering::StaticMeshIndex redTreeMesh;
      TorchManager torches;
      Simulation::CommandList simulationCommands;
      CommandList clientCommands;
      void writeCommands();
      void updateSimulation(double timeDelta);
      void setupPlayer(Rendering::BoneMeshIndex mesh, uint8_t pose);
      void setupMonster(Rendering::BoneMeshIndex mesh, uint8_t pose, float x, float z);
      void setupGround();
      void setupRock();
      void setupBox();
      void setupPointLight();
      void updateAtmosphereColor();
      void updateLightDirection();
      void configureGreenTree();
      void configureRedTree();
      void setupTree(float x, float z, Rendering::StaticMeshIndex mesh);
    };
  }
}

#endif
