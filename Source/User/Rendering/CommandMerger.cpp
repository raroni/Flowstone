#include "Core/Error.h"
#include "Rendering/CommandSorter.h"
#include "Rendering/CommandMerger.h"

namespace Rendering {
  CommandMerger::CommandMerger() : writer(buffer) { }

  void CommandMerger::merge(const CommandSorter &sorter) {
    writer.reset();
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
        case CommandType::DrawBoneMesh: {
          uint16_t length = sizeof(CommandType) + sizeof(DrawBoneMeshCommand);
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
