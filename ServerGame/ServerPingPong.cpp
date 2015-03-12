#include "ServerPingPong.h"

namespace ServerPingPong {
  static Piper::Server *pipe;

  void setPipe(Piper::Server *aPipe) {
    pipe = aPipe;
  }

  void handlePing(Piper::ClientID id) {

  }

  void update(double timeDelta) {
    /*
    for(uint8_t i=0; i<pipe->getClientCount(); ++i) {
      // what to do?
    }
    */
  }
}
