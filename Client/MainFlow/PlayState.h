#ifndef CLIENT_MAIN_FLOW_PLAY_STATE_H
#define CLIENT_MAIN_FLOW_PLAY_STATE_H

#include <stddef.h>
#include "Animation/Animator.h"
#include "Simulation/CommandList.h"
#include "Simulation/EventList.h"
#include "Simulation/PlayerHandle.h"
#include "Database/EntityHandle.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/StaticMeshIndex.h"
#include "Client/MainFlow/State.h"
#include "Client/CommandList.h"
#include "Client/AtmosphereColor.h"
#include "Client/TorchManager.h"
#include "Client/PlayMode.h"
#include "Client/RendererFeeder.h"
#include "Client/Interpolation/Interpolater.h"

namespace Rendering {
  class Renderer;
}

namespace Client {
  namespace MainFlow {
    class Manager;

    class PlayState : public State {
    public:
      PlayState(PlayMode playMode);
      void enter();
      void exit();
      void update(double deltaTime, const Keyboard &keyboard);
      State* checkTransition();
    private:
      Simulation::PlayerHandle playerID = -1;
      PlayMode playMode;
      uint8_t walkAnimationSkeleton;
      double stepTimeBank = 0;
      float timeOfDay = 0.3;
      RendererFeeder rendererFeeder;
      AtmosphereColor atmosphereColor;
      Rendering::StaticMeshIndex greenTreeMesh;
      Rendering::StaticMeshIndex redTreeMesh;
      Rendering::BoneMeshIndex characterMesh;
      TorchManager torches;
      Simulation::CommandList simulationCommands;
      Simulation::EventList simulationEvents;
      CommandList clientCommands;
      void configureAnimation();
      void configureRenderer();
      void processSimulationEvents();
      void writeCommands();
      void updateSimulation(double timeDelta);
      void setupMonster(::Database::EntityHandle monster);
      void setupGround();
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
