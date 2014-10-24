#ifndef MAIN_FLOW_SINGLE_PLAYER_H
#define MAIN_FLOW_SINGLE_PLAYER_H

#include <stddef.h>
#include <OpenGL/gl.h>
#include "MainFlow/State.h"
#include "ShaderRegistry.h"
#include "WorldRendering/Renderer.h"

namespace MainFlow {
  class Manager;

  class SinglePlayerState : public State {
    float x = 0;
    WorldRendering::Renderer renderer;
  public:
    SinglePlayerState(ShaderRegistry &registry) : renderer(registry) { }
    void enter() {
      renderer.initialize();

      unsigned int vertexCount = 4;
      WorldRendering::Vertex vertexData[vertexCount];
      vertexData[0] = { -0.5, 0.5, 0 };
      vertexData[1] = { 0.5, 0.5, 0 };
      vertexData[2] = { -0.5, -0.5, 0 };
      vertexData[3] = { 0.5, -0.5, 0 };

      uint16_t indexData[] = { 0, 2, 1, 1, 2, 3 };

      size_t vertexOffset = renderer.createVertexBuffer(vertexData, vertexCount);
      size_t indexOffset = renderer.createIndexBuffer(indexData, sizeof(indexData)/sizeof(uint16_t));

      renderer.createComponent(vertexOffset, indexOffset, -0.25);
      renderer.createComponent(vertexOffset, indexOffset, 0.25);
    }
    void update(double deltaTime) {
      renderer.draw();
      x += 0.1*deltaTime;
      glColor3f(1, .85, .35);
      glBegin(GL_TRIANGLES);
      {
        glVertex3f(x+ 0, 0.6, 0);
        glVertex3f(x+ -0.2, -0.3, 0);
        glVertex3f(x+.2, -.3, 0);
      }
      glEnd();
    }
    State* checkTransition() {
      return nullptr;
    }
  };
}

#endif
