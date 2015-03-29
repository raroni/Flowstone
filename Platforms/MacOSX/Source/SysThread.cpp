#include <pthread.h>
#include "SysThread.h"

namespace SysThread {
  void init(Thread *thread, void *(*routine)(void *)) {
    pthread_create(thread, NULL, routine, NULL);
  }

  void join(Thread *thread) {
    pthread_join(*thread, NULL);
  }

  void initMutex(Mutex *mutex) {
    pthread_mutex_init(mutex, NULL);
  }

  void destroyMutex(Mutex *mutex) {
    pthread_mutex_destroy(mutex);
  }

  bool lock(Mutex *mutex) {
    return pthread_mutex_lock(mutex) == 0;
  }

  bool tryLock(Mutex *mutex) {
    return pthread_mutex_trylock(mutex) == 0;
  }

  void unlock(Mutex *mutex) {
    pthread_mutex_unlock(mutex);
  }
}
