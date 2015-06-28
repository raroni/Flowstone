#include <unistd.h>
#include <sys/time.h>
#include "SysTime/SysTime.h"

namespace SysTime {
  USecond64 get() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec*1000000+tv.tv_usec);
  }

  void sleep(USecond64 duration) {
    usleep(static_cast<useconds_t>(duration));
  }
}
