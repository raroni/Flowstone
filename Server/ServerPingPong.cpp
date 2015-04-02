#include <string.h>
#include "Common/GameTime.h"
#include "Common/MessageType.h"
#include "ServerGameClientSet.h"
#include "Server/ServerNet.h"
#include "ServerPingPong.h"

namespace ServerPingPong {
  using namespace ServerGameClientSet;
  using namespace ServerGameClientSet::PingPong;

  static const double interval = 1.5;

  void handlePing(ServerGameClientID clientID, uint8_t pingID) {
    char message[2];
    message[0] = static_cast<char>(MessageType::Pong);
    memcpy(message+1, &pingID, 1);
    ServerNet::sendMessage(clientID, message, sizeof(message));
  }

  void handlePong(ServerGameClientID clientID, uint8_t pingID) {
    // todo: check if already received pong for pingID
    uint8_t index = indices[clientID];
    SysTime::MSecond32S packetRTT = GameTime::get()/1000-startTimes[index].list[pingID];
    SysTime::MSecond32S difference = packetRTT-rtts[index];
    rtts[index] += difference/10;
  }

  void update(double timeDelta) {
    for(uint8_t i=0; i<getCount(); ++i) {
      timeouts[i] -= timeDelta;
      if(timeouts[i] <= 0) {
        uint8_t nextID = nextIDs[i];
        startTimes[i].list[nextID] = GameTime::get()/1000;

        // todo: generalize this code, no need to do this manually on both client/server
        char message[2];
        message[0] = static_cast<char>(MessageType::Ping);
        memcpy(message+1, &nextID, 1);
        nextIDs[i]++;
        ServerNet::sendMessage(ids[i], message, sizeof(message));
        timeouts[i] += interval;
      }
    }
  }
}
