#include "ServerGame.h"

void ServerGame::initialize() {
  uint8_t ip[] = { 0, 0, 0, 0 };
  connectionPool.listen(ip, 4242);
}

void ServerGame::update(double timeDelta) {
  connectionPool.update(timeDelta);
}
