#ifndef SYSTHREAD_H
#define SYSTHREAD_H

#include "SysThread/Thread.h"
#include "SysThread/Mutex.h"

namespace SysThread {
  void init(Thread *thread, void *(*routine)(void *));
  void join(Thread *thread);
  void initMutex(Mutex *mutex);
  void destroyMutex(Mutex *mutex);
  bool lock(Mutex *mutex);
  bool tryLock(Mutex *mutex);
  void unlock(Mutex *mutex);
}

#endif
