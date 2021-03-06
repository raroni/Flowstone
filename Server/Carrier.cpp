#include <assert.h>
#include "Server/Net.h"
#include "Server/ClientSet.h"
#include "Server/Carrier.h"

namespace Server {
  namespace Carrier {
    using namespace ClientSet;
    using namespace ClientSet::Carrying;

    void remove(uint8_t clientIndex, uint16_t messageIndex) {
      counts[clientIndex]--;
      uint8_t count = counts[clientIndex];
      uint16_t *handles = handleSets[clientIndex].handles;
      Piper::Sequence *piperIDs = piperIDSets[clientIndex].ids;
      SysTime::MSecond16 *durations = durationSets[clientIndex].durations;
      float *timeouts = timeoutSets[clientIndex].timeouts;

      messageBuffers[clientIndex].release(handles[messageIndex]);
      piperIDs[messageIndex] = piperIDs[count];
      handles[messageIndex] = handles[count];
      durations[messageIndex] = durations[count];
      timeouts[messageIndex] = timeouts[count];
    }

    void update(double timeDelta) {
      for(uint8_t ci=0; ci<getCount(); ++ci) {
        SysTime::MSecond16 rtt = rtts[ci]/1000;
        ClientID clientID = ids[ci];
        for(uint8_t mi=0; mi<counts[ci]; ++mi) {
          SysTime::MSecond16 *durations = durationSets[ci].durations;
          SysTime::MSecond16 duration = durations[mi];
          float timeout = timeoutSets[ci].timeouts[mi];
          if(duration > rtt*timeout) {
            durations[mi] = 0;
            const void *message;
            uint16_t handle = handleSets[ci].handles[mi];
            uint16_t length = messageBuffers[ci].read(handle, &message);
            piperIDSets[ci].ids[mi] = Net::sendMessage(clientID, message, length);
          }
          else if(Net::getStatus(clientID, piperIDSets[ci].ids[mi]) == Piper::AckStatus::Yes) {
            remove(ci, mi);
            mi--;
          }
          assert(durations[mi] < UINT16_MAX-(1000*timeDelta));
          durations[mi] += 1000*timeDelta;
        }
      }
    }

    void send(ClientID clientID, const void *message, uint16_t length, float timeout) {
      uint8_t index = indices[clientID];
      uint8_t count = counts[index];
      assert(count != max);
      bool result = messageBuffers[index].write(
        handleSets[index].handles+count,
        message,
        length
      );
      assert(result); // todo: more appropriate false handling, such as disconnect
      durationSets[index].durations[count] = UINT16_MAX;
      timeoutSets[index].timeouts[count] = timeout;
      counts[index]++;
    }
  }
}
