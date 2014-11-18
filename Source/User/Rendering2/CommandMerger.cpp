#include "Core/Error.h"
#include "Rendering2/CommandSorter.h"
#include "Rendering2/CommandMerger.h"

#include <stdio.h>

namespace Rendering2 {
  void CommandMerger::merge(const CommandSorter &sorter) {
    count = 0;
    for(uint16_t i=0; sorter.getCount()>i; i++) {
      const char *command = sorter.get(i);
      CommandType type = *reinterpret_cast<const CommandType*>(command);
      switch(type) {
        case CommandType::ChangeShaderProgram: {
          uint16_t length = sizeof(CommandType) + sizeof(ShaderName);
          stream.writeRaw(command, length);
          break;
        }
        default: {
          fatalError("Cannot process command.");
          break;
        }
      }
      count++;
    }
  }

  uint16_t CommandMerger::getCount() const {
    return count;
  }

  const char* CommandMerger::getBuffer() const {
    return stream.getBuffer();
  }
}
