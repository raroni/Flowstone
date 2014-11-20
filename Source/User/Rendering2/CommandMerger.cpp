#include "Core/Error.h"
#include "Rendering2/CommandSorter.h"
#include "Rendering2/CommandMerger.h"

namespace Rendering2 {
  CommandMerger::CommandMerger() : writer(buffer) { }

  void CommandMerger::merge(const CommandSorter &sorter) {
    count = 0;
    for(uint16_t i=0; sorter.getCount()>i; i++) {
      const char *command = sorter.get(i);
      CommandType type = *reinterpret_cast<const CommandType*>(command);
      switch(type) {
        case CommandType::ChangeShaderProgram: {
          uint16_t length = sizeof(CommandType) + sizeof(ShaderName);
          writer.writeRaw(command, length);
          break;
        }
        case CommandType::DrawAnimatedMesh: {
          uint16_t length = sizeof(CommandType) + sizeof(DrawAnimatedMeshCommand);
          writer.writeRaw(command, length);
          break;
        }
        case CommandType::UpdateWorldViewTransform: {
          uint16_t length = sizeof(CommandType) + sizeof(UpdateWorldViewTransformCommand);
          writer.writeRaw(command, length);
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
    return buffer;
  }
}
