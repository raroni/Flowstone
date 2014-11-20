#ifndef Rendering_COMMAND_MERGER_H
#define Rendering_COMMAND_MERGER_H

#include "Rendering/Config.h"
#include "Rendering/CommandWriter.h"

namespace Rendering {
  class CommandSorter;

  class CommandMerger {
    uint16_t count = 0;
    char buffer[Config::commandBufferSize];
    CommandWriter writer;
  public:
    CommandMerger();
    void merge(const CommandSorter &sorter);
    uint16_t getCount() const;
    const char* getBuffer() const;
  };
}

#endif
