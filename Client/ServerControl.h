#ifndef CLIENT_SERVER_GUARD_H
#define CLIENT_SERVER_GUARD_H

namespace Client {
  namespace ServerControl {
    void initialize();
    void update();
    void requestInit();
    void sync();
    void requestTermination();
    void terminate();
  }
}

#endif
