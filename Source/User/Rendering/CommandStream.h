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
    void writeProgramChange(ProgramChangeCommand command);
    CommandType readType();
    ProgramChangeCommand readProgramChange();
  private:
    void writeType(CommandType type);
    uint16_t position = 0;
    char buffer[1024*10];
    uint16_t count = 0;
  };
}

#endif
