#include <pthread.h>
#include "SysThread.h"

namespace SysThread {
  void init(Thread *thread, void *(*routine)(void *)) {
    pthread_create(thread, NULL, routine, NULL);
  }

  void join(Thread thread) {
    pthread_join(thread, NULL);
  }
}
