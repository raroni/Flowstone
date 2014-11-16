#include "Rendering2/CommandMerger.h"

namespace Rendering2 {
  void CommandMerger::merge(const CommandStream &stream) {

  }

  uint16_t CommandMerger::getCount() const {
    return count;
  }

  const char* CommandMerger::getStream() const {
    return stream;
  }
}
