#include "Common/MessageType.h"
#include "ServerPingPong.h"
#include "ServerGame.h"

#include <stdio.h>

void ServerGame::initialize() {
  Piper::Address address;
  address.ip[0] = 0;
  address.ip[1] = 0;
  address.ip[2] = 0;
  address.ip[3] = 0;
  address.port = 4242;
  pipe.listen(address);

  ServerPingPong::configure(&pipe, &nextSequenceID);
}

void ServerGame::update(double timeDelta) {
  readPipe();

  // do game logic
  // ServerPingPong::update();

  pipe.dispatch();
}

void ServerGame::readPipe() {
  pipe.poll();

  const void *message = nullptr;
  uint16_t messageLength = 0;
  Piper::ClientID id;
  while(pipe.readMessage(&id, &message, &messageLength)) {
    if(!clientIDs[id]) {
      clientIDs[id] = true;
      // zomg new connection
      // put into active players or into rejection-queue (if full)
    }
    MessageType type = *static_cast<const MessageType*>(message);
    switch(type) {
      case MessageType::Ping:
        if(messageLength == 2) {
          uint8_t pingID = static_cast<const uint8_t*>(message)[1];
          ServerPingPong::handlePing(id, pingID);
        }
        break;
      default:
        printf("Server got something unknown.\n");
        break;
    }
  }
  // at some point later pipe.free(id);

  pipe.clear();
}
