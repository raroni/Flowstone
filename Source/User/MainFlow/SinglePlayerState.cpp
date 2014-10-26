#include "Rendering/Renderer.h"
#include "MainFlow/SinglePlayerState.h"

namespace MainFlow {
  SinglePlayerState::SinglePlayerState(Rendering::Renderer &renderer) : renderer(renderer) { }

  void SinglePlayerState::enter() {
    Rendering::Vertex vertexData[] = {
      // front
      { -0.5, 0.5, -0.5 },
      { 0.5, 0.5, -0.5 },
      { -0.5, -0.5, -0.5 },
      { 0.5, -0.5, -0.5 },

      { -0.5, 0.5, 0.5 },
      { 0.5, 0.5, 0.5 },
      { -0.5, -0.5, 0.5 },
      { 0.5, -0.5, 0.5 },
    };

    uint16_t indexData[] = {
      0, 2, 1, 1, 2, 3, // front
      1, 3, 7, 1, 7, 5, // right
      4, 7, 6, 4, 5, 7, // back
      0, 6, 2, 0, 4, 6, // right
      5, 0, 1, 5, 4, 0, // top
      2, 7, 3, 2, 6, 7  // bottom
    };

    Rendering::WorldRenderer &worldRenderer = renderer.getWorldRenderer();
    size_t vertexOffset = worldRenderer.createVertexBuffer(vertexData, sizeof(vertexData)/sizeof(Rendering::Vertex));
    size_t indexOffset = worldRenderer.createIndexBuffer(indexData, sizeof(indexData)/sizeof(uint16_t));
    worldRenderer.createComponent(vertexOffset, indexOffset);
    //worldRenderer.createComponent(vertexOffset, indexOffset);

    worldRenderer.cameraTransform.position[2] = -5;
  }

  void SinglePlayerState::update(double deltaTime) {
    /*
    Rendering::WorldRenderer &worldRenderer = renderer.getWorldRenderer();
    Rendering::Component *component = worldRenderer.getComponent(0);
    component->transform.position[0] += deltaTime;
    component->transform.position[1] += deltaTime*0.5;
    //worldRenderer.cameraTransform.position[0] += deltaTime;
    */
    Rendering::WorldRenderer &worldRenderer = renderer.getWorldRenderer();
    Rendering::Component *component = worldRenderer.getComponent(0);
    component->transform.rotateX(deltaTime);
    component->transform.rotateY(deltaTime*0.5);
  }

  State* SinglePlayerState::checkTransition() {
    return nullptr;
  }
}
