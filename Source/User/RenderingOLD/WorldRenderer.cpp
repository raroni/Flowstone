#include <math.h>
#include "Bro/Bro.h"
#include "Quanta/Math/Matrix4.h"
#include "Quanta/ProjectionFactory.h"
#include "Core/Error.h"
#include "Pose.h"
#include "Rendering/ShaderRegistry.h"
#include "Rendering/WorldRenderer.h"

namespace Rendering {
  struct GLAnimatedVertex {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLushort jointIndex;
  };

  WorldRenderer::WorldRenderer(::Rendering::ShaderRegistry &registry) : shaderRegistry(registry) { }

  void WorldRenderer::initialize() {
    GLint handle = shaderRegistry.getHandle(Rendering::ShaderName::Test);
    glUseProgram(handle);

    positionAttributeHandle = glGetAttribLocation(handle, "position");
    if(positionAttributeHandle == -1) {
      fatalError("Could not find position attribute handle.");
    }

    jointIndexAttributeHandle = glGetAttribLocation(handle, "jointIndex");
    if(jointIndexAttributeHandle == -1) {
      fatalError("Could not find joint attribute handle.");
    }

    GLint viewClipTransformationUniformHandle = glGetUniformLocation(handle, "viewClipTransformation");
    if(viewClipTransformationUniformHandle == -1) {
      fatalError("Could not find view clip transformation uniform handle.");
    }
    BroResolution resolution = broGetResolution();
    float aspectRatio = static_cast<float>(resolution.width)/(resolution.height);
    float fieldOfView = M_PI/3.0f;
    Quanta::Matrix4 viewClipTransformation = Quanta::ProjectionFactory::perspective(fieldOfView, aspectRatio, 0.1, 50);
    glUniformMatrix4fv(viewClipTransformationUniformHandle, 1, GL_FALSE, viewClipTransformation.components);

    worldViewTransformationUniformHandle = glGetUniformLocation(handle, "worldViewTransformation");
    if(worldViewTransformationUniformHandle == -1) {
      fatalError("Could not find world view transformation uniform handle.");
    }

    jointWorldTransformationUniformHandle = glGetUniformLocation(handle, "jointWorldTransformation");
    if(jointWorldTransformationUniformHandle == -1) {
      fatalError("Could not find joint world transformation uniform handle.");
    }

    modelJointTransformationsUniformHandle = glGetUniformLocation(handle, "modelJointTransformations");
    if(modelJointTransformationsUniformHandle == -1) {
      fatalError("Could not find model joint transformations uniform handle.");
    }

    glUseProgram(0);
  }

  size_t WorldRenderer::createAnimatedMesh(const AnimatedVertex *vertices, const size_t verticesLength, const uint16_t *indices, const size_t indicesLength) {
    GLuint vaoHandle;
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    glEnableVertexAttribArray(positionAttributeHandle);
    glEnableVertexAttribArray(jointIndexAttributeHandle);

    GLAnimatedVertex oglData[verticesLength];
    for(int i=0; verticesLength>i; i++) {
      GLAnimatedVertex *oglVertex = &oglData[i];
      const AnimatedVertex *inputData = &vertices[i];
      oglVertex->x = inputData->x;
      oglVertex->y = inputData->y;
      oglVertex->z = inputData->z;
      oglVertex->jointIndex = inputData->jointIndex;
    }
    GLuint vertexBufferHandle;
    glGenBuffers(1, &vertexBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(oglData), oglData, GL_STATIC_DRAW);

    glVertexAttribPointer(positionAttributeHandle, 3, GL_FLOAT, GL_FALSE, sizeof(GLAnimatedVertex), 0);
    glVertexAttribIPointer(jointIndexAttributeHandle, 1, GL_UNSIGNED_SHORT, sizeof(GLAnimatedVertex), reinterpret_cast<const GLvoid*>(sizeof(GLfloat)*3));

    GLushort indexData[indicesLength];
    for(int i=0; indicesLength>i; i++) {
      indexData[i] = indices[i];
    }
    GLuint indexBufferHandle;
    glGenBuffers(1, &indexBufferHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

    indexCounts[vaoCount] = indicesLength;
    vaoHandles[vaoCount] = vaoHandle;
    return vaoCount++;
  }

  void WorldRenderer::setPoses(const Pose *poses) {
    this->poses = poses;
  }

  void WorldRenderer::setJointWorldTransformations(const Quanta::Matrix4 *transformations) {
    jointWorldTransformations = transformations;
  }

  size_t WorldRenderer::createAnimatedMeshInstance(size_t vaoOffset, uint8_t interpolationTransformID) {
    AnimatedMeshInstance instance = { interpolationTransformID, vaoHandles[vaoOffset], indexCounts[vaoOffset] };
    animatedMeshInstances[animatedMeshInstanceCount++] = instance;
    return animatedMeshInstanceCount-1;
  }

  void WorldRenderer::draw() {
    glUseProgram(shaderRegistry.getHandle(Rendering::ShaderName::Test));
    glUniformMatrix4fv(worldViewTransformationUniformHandle, 1, GL_FALSE, cameraTransform.getInverseMatrix().components);

    for(int i=0; animatedMeshInstanceCount>i; i++) {
      AnimatedMeshInstance &instance = animatedMeshInstances[i];
      glUniformMatrix4fv(jointWorldTransformationUniformHandle, 1, GL_FALSE, jointWorldTransformations[instance.interpolationTransformID].components);
      const Pose *pose = &poses[i];
      glUniformMatrix4fv(modelJointTransformationsUniformHandle, 8, GL_FALSE, pose->joints[0].components);
      glBindVertexArray(instance.vaoHandle);
      glDrawElements(GL_TRIANGLES, instance.indexCount, GL_UNSIGNED_SHORT, 0);
    }

    glBindVertexArray(0);
    glUseProgram(0);
  }

  AnimatedMeshInstance* WorldRenderer::getAnimatedMeshInstance(size_t index) {
    return &animatedMeshInstances[index];
  }
}
