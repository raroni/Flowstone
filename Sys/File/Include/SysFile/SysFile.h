#ifndef SYSFILE_H

#include <stddef.h>

namespace SysFile {
  void readFile(const char *name, char *buffer, size_t bufferLength);
}

#endif
