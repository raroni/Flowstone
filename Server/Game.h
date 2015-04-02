#ifndef SERVER_GAME_H
#define SERVER_GAME_H

namespace Server {
  namespace Game {
    void initialize();
    void run();
    void terminate();
    void requestTermination();
  }
};

#endif
