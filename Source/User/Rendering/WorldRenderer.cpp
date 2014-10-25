#include <math.h>
#include "Bro/Bro.h"
#include "Quanta/Math/Matrix4.h"
#include "Quanta/ProjectionFactory.h"
#include "Core/Error.h"
#include "Rendering/ShaderRegistry.h"
#include "Rendering/WorldRenderer.h"

#include <stdio.h>

namespace Rendering {
  WorldRenderer::WorldRenderer(::Rendering::ShaderRegistry &registry) : shaderRegistry(registry) { }

  void WorldRenderer::initialize() {
    GLint handle = shaderRegistry.getHandle(Rendering::ShaderName::Test);

    positionAttributeHandle = glGetAttribLocation(handle, "position");
    if(positionAttributeHandle == -1) {
      fatalError("Could not find position attribute handle.");
    }

    glUseProgram(handle);
    GLint viewClipTransformationUniformHandle = glGetUniformLocation(handle, "viewClipTransformation");
    if(viewClipTransformationUniformHandle == -1) {
      fatalError("Could not find view clip transformation uniform handle.");
    }
    BroResolution resolution = broGetResolution();
    float aspectRatio = static_cast<float>(resolution.width)/(resolution.height);
    float fieldOfView = M_PI/3.0f;

    Quanta::Matrix4 viewClipTransformation = Quanta::ProjectionFactory::perspective(fieldOfView, aspectRatio, 0.1, 50);
    glUniformMatrix4fv(viewClipTransformationUniformHandle, 1, GL_FALSE, viewClipTransformation.components);
  }

  size_t WorldRenderer::createVertexBuffer(const Vertex *vertices, const size_t length) {
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

  size_t WorldRenderer::createIndexBuffer(uint16_t *indices, size_t length) {
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

  size_t WorldRenderer::createComponent(size_t vertexOffset, size_t indexOffset, float x) {
    Component component = { vertexBufferHandles[vertexOffset], indexBufferHandles[indexOffset], x };
    components[componentsCount++] = component;
    return componentsCount-1;
  }

  void WorldRenderer::draw() {
    glUseProgram(shaderRegistry.getHandle(Rendering::ShaderName::Test));
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

  Component* WorldRenderer::getComponent(size_t index) {
    return &components[index];
  }
}
