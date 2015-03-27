#ifndef USER_GAME_H
#define USER_GAME_H

// todo: fix hack
#include "ClientGame.h"

namespace UserGame {
  void run();
  void startServer();
  void requestTermination();
  extern ClientGame *stupidHack; // remember to remove header above
}

#endif
