// include <unistd.h>
#include <sys/time.h>
#include "SysTime/SysTime.h"

namespace SysTime {
  uint64_t get() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec*1000000+tv.tv_usec);
  }
}
