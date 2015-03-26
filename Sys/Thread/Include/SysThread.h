#ifndef SYSTHREAD_H
#define SYSTHREAD_H

#include "SysThread/Thread.h"

namespace SysThread {
  void init(Thread *thread, void *(*routine)(void *));
  void join(Thread thread);
}

#endif
