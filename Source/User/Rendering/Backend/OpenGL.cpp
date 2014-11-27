#include <OpenGL/gl3.h>
#include <cstddef>
#include "Core/Error.h"
#include "Rendering/AttributeLocation.h"
#include "Rendering/Backend/OpenGL.h"

namespace Rendering {
  namespace Backend {
    namespace OpenGL {
      struct GLBoneVertex {
        GLfloat px, py, pz;
        GLfloat nx, ny, nz;
        GLushort jointIndex;
      };

      static GLuint positionAttributeLocation = static_cast<GLuint>(AttributeLocation::Position);
      static GLuint normalAttributeLocation = static_cast<GLuint>(AttributeLocation::Normal);
      static GLuint jointIndexAttributeLocation = static_cast<GLuint>(AttributeLocation::JointIndex);

      ObjectHandle createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
        GLBoneVertex gpuVertices[vertexCount];
        for(uint16_t i=0; vertexCount>i; i++) {
          GLBoneVertex &gpuVertex = gpuVertices[i];
          const BoneVertex &vertex = vertices[i];
          gpuVertex.px = vertex.px;
          gpuVertex.py = vertex.py;
          gpuVertex.pz = vertex.pz;
          gpuVertex.nx = vertex.nx;
          gpuVertex.ny = vertex.ny;
          gpuVertex.nz = vertex.nz;
          gpuVertex.jointIndex = vertex.jointIndex;
        }
        GLushort gpuIndices[indexCount];
        for(uint16_t i=0; indexCount>i; i++) {
          gpuIndices[i] = indices[i];
        }

        GLuint handle;
        glGenVertexArrays(1, &handle);
        glBindVertexArray(handle);

        glEnableVertexAttribArray(positionAttributeLocation);
        glEnableVertexAttribArray(normalAttributeLocation);
        glEnableVertexAttribArray(jointIndexAttributeLocation);

        GLuint vertexBufferHandle;
        glGenBuffers(1, &vertexBufferHandle);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLBoneVertex)*vertexCount, gpuVertices, GL_STATIC_DRAW);

        GLuint indexBufferHandle;
        glGenBuffers(1, &indexBufferHandle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gpuIndices), gpuIndices, GL_STATIC_DRAW);

        glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GLBoneVertex), 0);
        glVertexAttribPointer(normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GLBoneVertex), reinterpret_cast<const GLvoid*>(sizeof(GLfloat)*3));
        glVertexAttribIPointer(jointIndexAttributeLocation, 1, GL_UNSIGNED_SHORT, sizeof(GLBoneVertex), reinterpret_cast<const GLvoid*>(sizeof(GLfloat)*6));

        glBindVertexArray(0);

        return static_cast<ObjectHandle>(handle);
      }

      ShaderHandle createShader(ShaderType type, const char *source) {
        GLenum oglType;
        switch(type) {
          case ShaderType::Vertex:
            oglType = GL_VERTEX_SHADER;
            break;
          case ShaderType::Fragment:
            oglType = GL_FRAGMENT_SHADER;
            break;
          default:
            fatalError("Unknown shader type.");
            break;
        }

        GLuint handle = glCreateShader(oglType);
        glShaderSource(handle, 1, &source, NULL);
        glCompileShader(handle);

        GLint compileSuccess;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &compileSuccess);
        if(compileSuccess == GL_FALSE) {
          GLint logLength;
          glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);
          GLchar *log = new GLchar[logLength+1];
          glGetShaderInfoLog(handle, logLength, NULL, log);
          fatalError(log);
          delete[] log;
        }

        return static_cast<ShaderHandle>(handle);
      }

      ProgramHandle createProgram() {
        GLuint handle = glCreateProgram();
        return static_cast<ProgramHandle>(handle);
      }

      void linkProgram(ProgramHandle handle) {
        GLuint oglHandle = handle;
        glLinkProgram(oglHandle);
        GLint linkSuccess;
        glGetProgramiv(oglHandle, GL_LINK_STATUS, &linkSuccess);
        if(linkSuccess == GL_FALSE) {
          fatalError("GL program linking failed.");
        }
      }

      void attachShader(ProgramHandle program, ShaderHandle shader) {
        glAttachShader(program, shader);
      }
    }
  }
}
