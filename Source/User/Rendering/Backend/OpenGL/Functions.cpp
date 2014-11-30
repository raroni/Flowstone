#include <OpenGL/gl3.h>
#include <cstddef>
#include "Core/Error.h"
#include "Rendering/Backend/Functions.h"

namespace Rendering {
  namespace Backend {
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

    ObjectHandle createObject() {
      GLuint handle;
      glGenVertexArrays(1, &handle);
      return static_cast<ObjectHandle>(handle);
    }

    void enableAttributeLocation(AttributeLocation location) {
      glEnableVertexAttribArray(static_cast<GLuint>(location));
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

    void setProgram(ProgramHandle program) {
      glUseProgram(static_cast<GLuint>(program));
    }

    UniformHandle getUniform(ProgramHandle program, const char *name) {
      return glGetUniformLocation(program, name);
    }

    UniformBlockHandle getUniformBlock(ProgramHandle program, const char *name) {
      return glGetUniformBlockIndex(program, name);
    }

    void clear() {
      glClear(GL_COLOR_BUFFER_BIT);
    }

    void setClearColor(float red, float green, float blue) {
      glClearColor(red, green, blue, 1);
    }

    void setUniformMat4(UniformHandle uniform, uint8_t count, const float *data) {
      glUniformMatrix4fv(uniform, count, GL_FALSE, data);
    }

    void setObject(ObjectHandle object) {
      glBindVertexArray(object);
    }

    void drawIndexed(uint16_t indexCount) {
      glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, 0);
    }

    BufferHandle createBuffer() {
      GLuint handle;
      glGenBuffers(1, &handle);
      return handle;
    }

    void writeBuffer(BufferTarget target, uint16_t size, const void *data) {
      glBufferData(static_cast<GLenum>(target), size, data, GL_STREAM_DRAW);
    }

    void setBuffer(BufferTarget target, BufferHandle buffer) {
      glBindBuffer(static_cast<GLenum>(target), buffer);
    }

    void setBufferIndex(BufferTarget target, BufferHandle buffer, uint8_t index) {
      glBindBufferBase(static_cast<GLenum>(target), index, buffer);
    }

    void setUniformBlockIndex(ProgramHandle program, UniformBlockHandle block, uint8_t index) {
      glUniformBlockBinding(program, block, index);
    }

    void configureAttribute(AttributeLocation location, uint8_t count, Backend::DataType dataType, uint8_t stride, uint8_t offset) {
      switch(dataType) {
        case DataType::Float:
          glVertexAttribPointer(location, count, static_cast<GLenum>(dataType), GL_FALSE, stride, reinterpret_cast<const GLvoid*>(offset));
          break;
        case DataType::UnsignedShort:
        case DataType::UnsignedByte:
          glVertexAttribIPointer(location, count, static_cast<GLenum>(dataType), stride, reinterpret_cast<const GLvoid*>(offset));
          break;
        default:
          fatalError("Unknown data type.");
          break;
      }
    }
  }
}
