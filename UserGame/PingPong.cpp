#include <string.h>
#include "Common/GameTime.h"
#include "Common/MessageType.h"
#include "ClientNet.h"
#include "PingPong.h"

namespace PingPong {
  static double timeUntilPing = 0;
  static const double interval = 1.5;
  uint8_t nextPingID = 0;

  uint32_t rtt = 0;

  uint64_t startTimes[UINT8_MAX];

  GameTime::MSecond16 getRTT() {
    return rtt/1000;
  }

  void update(double timeDelta) {
    timeUntilPing -= timeDelta;
    if(timeUntilPing <= 0) {
      startTimes[nextPingID] = GameTime::get();

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
    int32_t packetRTT = GameTime::get()-startTimes[pingID];
    int32_t difference = packetRTT-rtt;
    rtt += difference/10;
  }

  void handlePing(uint8_t pingID) {
    char message[2];
    message[0] = static_cast<char>(MessageType::Pong);
    memcpy(message+1, &pingID, 1);
    ClientNet::sendMessage(message, sizeof(message));
  }
}
