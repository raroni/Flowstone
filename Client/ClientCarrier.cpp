#include <assert.h>
#include "Common/LoopStream.h"
#include "PingPong.h"
#include "ClientNet.h"
#include "ClientCarrier.h"

namespace ClientCarrier {
  const uint8_t max = 128;
  SysTime::MSecond16 durations[max];
  float timeouts[max];
  uint16_t handles[max];
  uint8_t count = 0;
  Piper::Sequence piperIDs[max];

  static const uint16_t messageCapacity = 1024*20;
  struct {
    uint16_t offsets[max];
    uint16_t lengths[max];
    char storage[messageCapacity];
  } messageData;
  LoopStream messages(
    messageData.offsets,
    messageData.lengths,
    max,
    messageData.storage,
    messageCapacity
  );

  void remove(uint16_t index) {
    count--;
    messages.release(handles[index]);
    piperIDs[index] = piperIDs[count];
    handles[index] = handles[count];
    durations[index] = durations[count];
    timeouts[index] = timeouts[count];
  }

  void update(double timeDelta) {
    // todo: should check connection monitor here instead
    if(PingPong::getRTT() == 0) return;

    for(uint16_t i=0; i<count; ++i) {
      if(durations[i] > PingPong::getRTT()*timeouts[i]) {
        durations[i] = 0;
        const void *message;
        uint16_t length = messages.read(handles[i], &message);
        piperIDs[i] = ClientNet::sendMessage(message, length);
      }
      else if(ClientNet::getStatus(piperIDs[i]) == Piper::AckStatus::Yes) {
        remove(i);
        i--;
      }

      // todo: better handling, disconnect?
      assert(durations[i] < UINT16_MAX-(1000*timeDelta));
      durations[i] += 1000*timeDelta;
    }
  }

  void send(const void *message, uint16_t length, float timeout) {
    assert(count != max);
    bool result = messages.write(handles+count, message, length);
    assert(result); // todo more appropriate false handling, such as disconnect
    durations[count] = UINT16_MAX;
    timeouts[count] = timeout;
    count++;
  }
}
