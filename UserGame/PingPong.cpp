#include <string.h>
#include "Common/GameTime.h"
#include "Common/MessageType.h"
#include "ClientNet.h"
#include "PingPong.h"

namespace PingPong {
  static GameTime::MSecond16S timeUntilPing = 0;
  static const GameTime::MSecond16 interval = 1500;
  uint8_t nextPingID = 0;
  GameTime::MSecond16 rtt = 250;
  GameTime::MSecond32 startTimes[UINT8_MAX];

  GameTime::MSecond16 getRTT() {
    return rtt;
  }

  void update(double timeDelta) {
    timeUntilPing -= timeDelta*1000;
    if(timeUntilPing <= 0) {
      startTimes[nextPingID] = GameTime::get()/1000;

      // todo: generalize this code, no need to do this manually on both client/server
      char message[2];
      message[0] = static_cast<char>(MessageType::Ping);
      memcpy(message+1, &nextPingID, 1);
      nextPingID++;
      ClientNet::sendMessage(message, sizeof(message));
      timeUntilPing += interval;
    }
  }

  void handlePong(uint8_t pingID) {
    // todo: check if already received pong for pingID
    GameTime::MSecond32S packetRTT = GameTime::get()/1000-startTimes[pingID];
    GameTime::MSecond32S difference = packetRTT-rtt;
    rtt += difference/10;
  }

  void handlePing(uint8_t pingID) {
    char message[2];
    message[0] = static_cast<char>(MessageType::Pong);
    memcpy(message+1, &pingID, 1);
    ClientNet::sendMessage(message, sizeof(message));
  }
}
