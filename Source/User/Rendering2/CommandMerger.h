#include "Rendering2/Config.h"

namespace Rendering2 {
  class CommandStream;

  class CommandMerger {
    char stream[Config::commandStreamSize];
    uint16_t count = 0;
  public:
    void merge(const CommandStream &stream);
    uint16_t getCount() const;
    const char* getStream() const;
  };
}
