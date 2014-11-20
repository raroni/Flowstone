#include <math.h>
#include "Quanta/ProjectionFactory.h"
#include "Core/Error.h"
#include "Bro/Bro.h"
#include "Rendering/CommandType.h"
#include "Rendering/OpenGL/ShaderLoading.h"
#include "Rendering/CommandReader.h"
#include "Rendering/OpenGL/Backend.h"

namespace Rendering {
  namespace OpenGL {
    void Backend::initialize() {
      loadShaders(shaderRegistry);
      glClearColor(1, 0, 0, 1);
      glEnable(GL_CULL_FACE);

      GLint handle = shaderRegistry.getHandle(ShaderName::Animated);
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
      configureBoneMeshRegistry();
    }

    void Backend::configureBoneMeshRegistry() {
      boneMeshRegistry.positionAttributeHandle = positionAttributeHandle;
      boneMeshRegistry.jointIndexAttributeHandle = jointIndexAttributeHandle;
    }

    void Backend::clear() {
      glClear(GL_COLOR_BUFFER_BIT);
    }

    BoneMeshIndex Backend::createBoneMesh(const AnimatedVertex *vertices, const size_t vertexCount, const uint16_t *indices, const size_t indexCount) {
      return boneMeshRegistry.create(vertices, vertexCount, indices, indexCount);
    }

    void Backend::draw(const char *stream, uint16_t count) {
      CommandReader reader(stream);
      for(uint16_t i=0; count>i; i++) {
        CommandType type = reader.readType();
        switch(type) {
          case CommandType::ChangeShaderProgram: {
            ChangeShaderProgramCommand command = reader.readChangeShaderProgram();
            glUseProgram(shaderRegistry.getHandle(command.shader));
            break;
          }
          case CommandType::UpdateWorldViewTransform: {
            UpdateWorldViewTransformCommand command = reader.readUpdateWorldViewTransform();
            glUniformMatrix4fv(worldViewTransformationUniformHandle, 1, GL_FALSE, command.matrix);
            break;
          }
          case CommandType::DrawBoneMesh: {
            DrawBoneMeshCommand command = reader.readDrawBoneMesh();
            BoneMesh mesh = boneMeshRegistry.get(command.meshIndex);
            glUniformMatrix4fv(jointWorldTransformationUniformHandle, 1, GL_FALSE, command.transform.components);
            glUniformMatrix4fv(modelJointTransformationsUniformHandle, 8, GL_FALSE, command.pose.joints[0].components);
            glBindVertexArray(mesh.vaoHandle);
            glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_SHORT, 0);
            break;
          }
          default: {
            fatalError("Could not execute command.");
            break;
          }
        }
      }
    }
  }
}
