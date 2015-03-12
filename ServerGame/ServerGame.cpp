#include <stdio.h>
#include "ServerPingPong.h"
#include "ServerGame.h"

void ServerGame::initialize() {
  Piper::Address address;
  address.ip[0] = 0;
  address.ip[1] = 0;
  address.ip[2] = 0;
  address.ip[3] = 0;
  address.port = 4242;
  pipe.listen(address);

  ServerPingPong::setPipe(&pipe);
}

void ServerGame::update(double timeDelta) {
  readPipe();

  // do game logic
  // ServerPingPong::update();

  //pipe.dispatch();
}

void ServerGame::readPipe() {
  pipe.poll();

  const void *message = nullptr;
  uint16_t messageLength = 0;
  Piper::ClientID id;
  while(pipe.readMessage(&id, &message, &messageLength)) {
    if(!clientIDs[id]) {
      clientIDs[id] = true;
      printf("Got new connection!\n");
      // zomg new connection
      // put into active players or into rejection-queue (if full)
    }
    printf("Got something from client %d!\n", id);
  }
  // at some point later pipe.free(id);

  pipe.clear();
}
