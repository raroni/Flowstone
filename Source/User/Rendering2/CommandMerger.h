#ifndef RENDERING2_COMMAND_MERGER_H
#define RENDERING2_COMMAND_MERGER_H

#include "Rendering2/Config.h"
#include "Rendering2/CommandWriter.h"

namespace Rendering2 {
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
