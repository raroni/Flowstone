#ifndef SYSGFX_DATA_TYPE_H
#define SYSGFX_DATA_TYPE_H

#include <OpenGL/gl3.h>

namespace SysGFX {
  enum class DataType {
    Float = GL_FLOAT,
    UnsignedShort = GL_UNSIGNED_SHORT,
    UnsignedByte = GL_UNSIGNED_BYTE
  };
}

#endif
