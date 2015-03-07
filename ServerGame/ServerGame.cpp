#include "ServerGame.h"

void ServerGame::initialize() {

}

void ServerGame::update(double timeDelta) {
  connectionPool.update(timeDelta);
}
