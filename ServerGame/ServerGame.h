#ifndef SERVER_GAME_H
#define SERVER_GAME_H

class ServerGame {
public:
  void initialize();
  void update(double timeDelta);
  void readPipe();
};

#endif
