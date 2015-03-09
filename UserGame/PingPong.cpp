#include "PingPong.h"

namespace PingPong {
  Piper::Client *pipe;
  static double timeUntilPing = 0;
  static const double interval = 0.5;

  void setPipe(Piper::Client &aPipe) {
    pipe = &aPipe;
  }

  void update(double timeDelta) {
    timeUntilPing -= timeDelta;
    if(timeUntilPing <= 0) {
      Piper::Sequence id = pipe->createID();
      pipe->sendMessage(id, "hey", 4);
      timeUntilPing += interval;
    }
  }
}
