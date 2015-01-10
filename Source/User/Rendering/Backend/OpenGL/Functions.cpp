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

    void attachRenderBuffer(RenderBufferHandle renderBuffer) {
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
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

    void clear(ClearBitMask mask) {
      glClear(static_cast<GLbitfield>(mask));
    }

    void setClearColor(float red, float green, float blue) {
      glClearColor(red, green, blue, 1);
    }

    void setUniformMat4(UniformHandle uniform, uint8_t count, const float *data) {
      glUniformMatrix4fv(uniform, count, GL_FALSE, data);
    }

    void setUniformVec3(UniformHandle uniform, uint8_t count, const float *data) {
      glUniform3fv(uniform, count, data);
    }

    void setUniformVec2(UniformHandle uniform, uint8_t count, const float *data) {
      glUniform2fv(uniform, count, data);
    }

    void setUniformFloat(UniformHandle uniform, uint8_t count, const float *data) {
      glUniform1fv(uniform, count, data);
    }

    void setUniformInt(UniformHandle uniform, int data) {
      glUniform1i(uniform, data);
    }

    void setUniformUInt(UniformHandle uniform, unsigned int data) {
      glUniform1ui(uniform, data);
    }

    void setObject(ObjectHandle object) {
      glBindVertexArray(object);
    }

    void drawIndexed(uint16_t indexCount, DataType dataType) {
      glDrawElements(GL_TRIANGLES, indexCount, static_cast<GLenum>(dataType), 0);
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

    void setTexture(TextureHandle texture) {
      glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(texture));
    }

    void writeTexture(uint16_t width, uint16_t height, TextureFormat format, const void *data) {
      GLenum dataFormat = GL_RGB;
      GLenum dataType = GL_FLOAT;
      if(format == TextureFormat::Depth) {
        dataFormat = GL_DEPTH_COMPONENT;
        dataType = GL_FLOAT;
      }

      glTexImage2D(
        GL_TEXTURE_2D,
        0,
        static_cast<GLint>(format),
        width,
        height,
        0,
        dataFormat,
        dataType,
        data
      );
    }

    void setTextureWrap(Backend::TextureWrap wrap) {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrap));
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrap));
    }

    void setTextureFilter(Backend::TextureFilter filter) {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter));
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filter));
    }

    TextureHandle createTexture() {
      GLuint texture;
      glGenTextures(1, &texture);
      return texture;
    }

    void disableDrawBuffer() {
      glDrawBuffer(GL_NONE);
    }

    void attachColorTexture(TextureHandle texture, uint8_t location) {
      glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+location, texture, 0);
    }

    void attachDepthTexture(TextureHandle texture) {
      glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
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

    RenderTargetHandle createRenderTarget() {
      GLuint handle;
      glGenFramebuffers(1, &handle);
      return handle;
    }

    void setRenderTarget(RenderTargetHandle renderTarget) {
      glBindFramebuffer(GL_FRAMEBUFFER, renderTarget);
    }

    bool checkRenderTarget() {
      GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      return status == GL_FRAMEBUFFER_COMPLETE;
    }

    void setDrawBufferCount(uint8_t count) {
      GLenum buffers[count];
      for(uint8_t i=0; count>i; i++) {
        buffers[i] = GL_COLOR_ATTACHMENT0+i;
      }
      glDrawBuffers(count, buffers);
    }

    void setTextureUnit(uint8_t unit) {
      glActiveTexture(GL_TEXTURE0 + unit);
    }

    void setRenderBuffer(RenderBufferHandle renderBuffer) {
      glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    }

    void enableDepthTest() {
      glEnable(GL_DEPTH_TEST);
    }

    void disableDepthTest() {
      glDisable(GL_DEPTH_TEST);
    }

    void setCullFace(CullFace face) {
      glCullFace(static_cast<GLenum>(face));
    }

    RenderBufferHandle createRenderBuffer(uint16_t width, uint16_t height) {
      GLuint buffer;
      glGenRenderbuffers(1, &buffer);
      glBindRenderbuffer(GL_RENDERBUFFER, buffer);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
      glBindRenderbuffer(GL_RENDERBUFFER, 0);
      return buffer;
    }

    void enableFaceCulling() {
      glEnable(GL_CULL_FACE);
    }

    void setViewport(uint16_t width, uint16_t height) {
      glViewport(0, 0, width, height);
    }
  }
}
