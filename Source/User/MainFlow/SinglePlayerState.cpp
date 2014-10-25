#include "Rendering/Renderer.h"
#include "MainFlow/SinglePlayerState.h"

namespace MainFlow {
  SinglePlayerState::SinglePlayerState(Rendering::Renderer &renderer) : renderer(renderer) { }

  void SinglePlayerState::enter() {
    unsigned int vertexCount = 4;
    Rendering::Vertex vertexData[vertexCount];
    vertexData[0] = { -0.5, 0.5, 3 };
    vertexData[1] = { 0.5, 0.5, 3 };
    vertexData[2] = { -0.5, -0.5, 3 };
    vertexData[3] = { 0.5, -0.5, 3 };

    uint16_t indexData[] = { 0, 2, 1, 1, 2, 3 };

    Rendering::WorldRenderer &worldRenderer = renderer.getWorldRenderer();
    size_t vertexOffset = worldRenderer.createVertexBuffer(vertexData, vertexCount);
    size_t indexOffset = worldRenderer.createIndexBuffer(indexData, sizeof(indexData)/sizeof(uint16_t));
    worldRenderer.createComponent(vertexOffset, indexOffset, -0.25);
    worldRenderer.createComponent(vertexOffset, indexOffset, 0.25);
  }

  void SinglePlayerState::update(double deltaTime) {
    Rendering::WorldRenderer &worldRenderer = renderer.getWorldRenderer();
    worldRenderer.cameraTransform.position[0] += deltaTime;
  }

  State* SinglePlayerState::checkTransition() {
    return nullptr;
  }
}
