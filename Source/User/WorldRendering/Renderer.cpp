#include "Core/Error.h"
#include "ShaderRegistry.h"
#include "WorldRendering/Renderer.h"

namespace WorldRendering {
  Renderer::Renderer(ShaderRegistry &registry) : shaderRegistry(registry) { }
  
  void Renderer::initialize() {
    glGetUniformLocation(positionAttributeHandle, "modelPosition");
    if(positionAttributeHandle == -1) {
      fatalError("Could not find position attribute handle.");
    }
  }

  size_t Renderer::createVertexBuffer(const Vertex *vertices, const size_t length) {
    GLfloat data[length*3];
    for(int i=0; length>i; i++) {
      int offset = i*3;
      data[offset] = vertices[i].x;
      data[offset+1] = vertices[i].y;
      data[offset+2] = vertices[i].z;
    }

    glGenBuffers(1, &vertexBufferHandles[vertexBufferHandleCount]);
    GLuint handle = vertexBufferHandles[vertexBufferHandleCount];
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vertexBufferHandleCount++;
  }

  size_t Renderer::createIndexBuffer(uint16_t *indices, size_t length) {
    GLushort data[length];
    for(int i=0; length>i; i++) {
      data[i] = indices[i];
    }

    glGenBuffers(1, &indexBufferHandles[indexBufferHandleCount]);
    GLuint handle = indexBufferHandles[indexBufferHandleCount];
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return indexBufferHandleCount++;
  }

  size_t Renderer::createComponent(size_t vertexOffset, size_t indexOffset, float x) {
    Component component = { vertexBufferHandles[vertexOffset], indexBufferHandles[indexOffset], x };
    components[componentsCount++] = component;
    return componentsCount-1;
  }

  void Renderer::draw() {
    glUseProgram(shaderRegistry.getHandle(ShaderName::Test));
    glEnableVertexAttribArray(positionAttributeHandle);
    for(int i=0; componentsCount>i; i++) {
      glBindBuffer(GL_ARRAY_BUFFER, components[i].vertexBufferHandle);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, components[i].indexBufferHandle);
      glVertexAttribPointer(positionAttributeHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(positionAttributeHandle);
    glUseProgram(0);
  }

  Component* Renderer::getComponent(size_t index) {
    return &components[index];
  }
}
