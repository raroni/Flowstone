#include <assert.h>
#include "ServerGame/ServerNet.h"
#include "ServerGame/ServerGameClientSet.h"
#include "ServerGame/ServerCarrier.h"

#include <stdio.h>

namespace ServerCarrier {
  using namespace ServerGameClientSet;
  using namespace ServerGameClientSet::Carrying;

  void update(double timeDelta) {
    for(uint8_t ci=0; ci<getCount(); ++ci) {
      GameTime::MSecond16 rtt = rtts[ci]/1000;
      for(uint8_t mi=0; mi<counts[ci]; ++mi) {
        GameTime::MSecond16 *durations = durationSets[ci].durations;
        GameTime::MSecond16 duration = durations[mi];
        float timeout = timeoutSets[ci].timeouts[mi];
        //printf("%d > %d*%f\n", duration, rtt, timeout);
        if(duration > rtt*timeout) {
          durations[mi] = 0;
          const void *message;
          uint16_t handle = handleSets[ci].handles[mi];
          uint16_t length = messageBuffers[ci].read(handle, &message);
          ServerGameClientID clientID = ids[ci];
          piperIDSets[ci].ids[mi] = ServerNet::sendMessage(clientID, message, length);
          printf("Sent!\n");
        }
        /*
        else if(ClientNet::getStatus(piperIDs[i]) == Piper::AckStatus::Yes) {
          printf("Yeah delivered! Crash and burn!\n");
          assert(false);
          remove(i);
          i--;
        }
        */
        assert(durations[mi] < UINT16_MAX-(1000*timeDelta));
        durations[mi] += 1000*timeDelta;
      }
    }

    /*
    for(uint16_t i=0; i<ClientSet::getCount(); ++i) {
      if(durations[i] > rtts[i]*timeouts[i]) {
        durations[i] = 0;
        const void *message;
        uint16_t length = messages.read(handles[i], &message);
        piperIDs[i] = ClientNet::sendMessage(message, length);
      }
      else if(ClientNet::getStatus(piperIDs[i]) == Piper::AckStatus::Yes) {
        remove(i);
        i--;
      } else {
      }

      // todo: better handling, disconnect?
      assert(durations[i] < UINT16_MAX-(1000*timeDelta));
      durations[i] += 1000*timeDelta;
    }
    */
  }

  void send(ServerGameClientID clientID, const void *message, uint16_t length, float timeout) {
    uint8_t index = indices[clientID];
    uint8_t count = counts[index];
    assert(count != max);
    bool result = messageBuffers[index].write(
      handleSets[index].handles+count,
      message,
      length
    );
    assert(result); // todo more appropriate false handling, such as disconnect
    durationSets[index].durations[count] = UINT16_MAX;
    timeoutSets[index].timeouts[count] = timeout;
    counts[index]++;
  }

  void remove(uint8_t clientIndex, uint16_t messageIndex) {

  }
}
