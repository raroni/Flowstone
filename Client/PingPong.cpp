#include <string.h>
#include "Misc/GameTime.h"
#include "Misc/MessageType.h"
#include "Net.h"
#include "PingPong.h"

namespace Client {
  namespace PingPong {
    static SysTime::MSecond16S timeUntilPing = 0;
    static const SysTime::MSecond16 interval = 1500;
    uint8_t nextPingID = 0;
    SysTime::MSecond16 rtt = 250;
    SysTime::MSecond32 startTimes[UINT8_MAX];

    SysTime::MSecond16 getRTT() {
      return rtt;
    }

    void update(double timeDelta) {
      timeUntilPing -= timeDelta*1000;
      if(timeUntilPing <= 0) {
        startTimes[nextPingID] = static_cast<SysTime::MSecond32>(GameTime::get()/1000);

        // todo: generalize this code, no need to do this manually on both client/server
        char message[2];
        message[0] = static_cast<char>(MessageType::Ping);
        memcpy(message+1, &nextPingID, 1);
        nextPingID++;
        Net::sendMessage(message, sizeof(message));
        timeUntilPing += interval;
      }
    }

    void handlePong(uint8_t pingID) {
      // todo: check if already received pong for pingID
      SysTime::MSecond32S packetRTT = static_cast<SysTime::MSecond32S>(GameTime::get()/1000-startTimes[pingID]);
      SysTime::MSecond32S difference = packetRTT-rtt;
      rtt += difference/10;
    }

    void handlePing(uint8_t pingID) {
      char message[2];
      message[0] = static_cast<char>(MessageType::Pong);
      memcpy(message+1, &pingID, 1);
      Net::sendMessage(message, sizeof(message));
    }
  }
}
