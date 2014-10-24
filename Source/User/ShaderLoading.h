#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "Cabi/Cabi.h"
#include "ShaderRegistry.h"

static void link(GLuint programHandle, GLuint vertexHandle, GLuint fragmentHandle) {
    glAttachShader(programHandle, vertexHandle);
    glAttachShader(programHandle, fragmentHandle);
    glLinkProgram(programHandle);
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    if(linkSuccess == GL_FALSE) {
      printf("GL program linking failed.");
      exit(1);
    }
}

static GLuint compileShader(GLuint handle, const char *source, GLenum type) {
    glShaderSource(handle, 1, &source, NULL);
    glCompileShader(handle);

    GLint compileSuccess;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compileSuccess);
    if(compileSuccess == GL_TRUE) {
      return handle;
    } else {
        GLint logLength;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);
        GLchar *log = new GLchar[logLength+1];
        glGetShaderInfoLog(handle, logLength, NULL, log);
        printf("Shader compilation error:\n");
        printf("%s\n", log);
        delete[] log;
        exit(1);
    }
}

const static size_t sourceLength = 4096;

static GLuint setupShader(const char *filename, GLenum type) {
  char path[128] = "Shaders/";
  strcat(path, filename);
  if(type == GL_VERTEX_SHADER) {
    strcat(path, ".vert");
  } else {
    strcat(path, ".frag");
  }

  char source[sourceLength] = {};
  cabiReadFile(path, source, sourceLength);

  GLuint handle = glCreateShader(type);
  compileShader(handle, source, type);
  return handle;
}

static void load(ShaderRegistry &registry, const char *filename, ShaderName registryName) {
  GLuint programHandle = glCreateProgram();
  GLuint vertexHandle = setupShader(filename, GL_VERTEX_SHADER);
  GLuint fragmentHandle = setupShader(filename, GL_FRAGMENT_SHADER);
  link(programHandle, vertexHandle, fragmentHandle);
  registry.addHandle(registryName, programHandle);
}

void loadShaders(ShaderRegistry &registry) {
  load(registry, "Test", ShaderName::Test);
}
