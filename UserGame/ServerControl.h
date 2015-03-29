#ifndef SERVER_GUARD_H
#define SERVER_GUARD_H

namespace ServerControl {
  void initialize();
  void update();
  void requestInit();
  void sync();
  void requestTermination();
  void terminate();
}

#endif
