#include <string.h>
#include "Common/GameTime.h"
#include "Common/MessageType.h"
#include "PingPong.h"

#include <stdio.h>
#include <inttypes.h>

namespace PingPong {
  Piper::Client *pipe;
  static double timeUntilPing = 0;
  static const double interval = 1.5;
  uint8_t nextPingID = 0;

  uint32_t rtt = 0;

  uint64_t startTimes[UINT8_MAX];

  void setPipe(Piper::Client &aPipe) {
    pipe = &aPipe;
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
      pipe->sendMessage(message, sizeof(message));
      timeUntilPing += interval;
    }
  }

  void handlePong(uint8_t pingID) {
    int32_t packetRTT = GameTime::get()-startTimes[pingID];
    int32_t difference = packetRTT-rtt;
    rtt += difference/10;
  }
}
