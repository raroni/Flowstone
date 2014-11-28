#ifndef RENDERING_COMMAND_STREAM_H
#define RENDERING_COMMAND_STREAM_H

#include "Rendering/Commands.h"
#include "Rendering/CommandType.h"

namespace Rendering {
  class CommandStream {
  public:
    void reset();
    void rewind();
    uint16_t getCount() { return count; }
    void writeIndexedDraw(IndexedDrawCommand command);
    void writeObjectSet(ObjectSetCommand command);
    void writeProgramSet(ProgramSetCommand command);
    void writeUniformMat4Set(UniformMat4SetCommand command);
    void writeUniform8Mat4Set(Uniform8Mat4SetCommand command);
    CommandType readType();
    IndexedDrawCommand readIndexedDraw();
    ObjectSetCommand readObjectSet();
    ProgramSetCommand readProgramSet();
    UniformMat4SetCommand readUniformMat4Set();
    Uniform8Mat4SetCommand readUniform8Mat4Set();
  private:
    void writeType(CommandType type);
    uint16_t position = 0;
    char buffer[1024*10];
    uint16_t count = 0;
  };
}

#endif
