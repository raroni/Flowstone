#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

namespace ClientGame {
  void initialize();
  void update(double timeDelta);
  void terminate();
  void requestTermination();
  bool shouldTerminate();
}

#endif
