#include <assert.h>
#include <string.h>
#include "Server/ClientIDPool.h"
#include "Server/ClientSet.h"

// dummy:
#include "Server/Carrier.h"
#include "Common/MessageType.h"

namespace Server {
  namespace ClientSet {
    static ClientIDPool idPool;

    int8_t indicesByPiperIDs[Piper::Config::Server::clientMax] = { -1 };
    uint8_t indices[Config::clientMax];
    ClientID ids[Config::clientMax];
    Piper::ClientID piperIDs[Config::clientMax];
    uint8_t sendCounts[Config::clientMax];
    SysTime::MSecond16 rtts[Config::clientMax] = { 250 };
    uint8_t count = 0;

    namespace PingPong {
      StartTimeSet startTimes[Config::clientMax];
      double timeouts[Config::clientMax];
      uint8_t nextIDs[Config::clientMax];
    }

    namespace Carrying {
      uint8_t counts[Config::clientMax];
      DurationSet durationSets[Config::clientMax];
      TimeoutSet timeoutSets[Config::clientMax];
      HandleSet handleSets[Config::clientMax];
      PiperIDSet piperIDSets[Config::clientMax];
      LoopStream messageBuffers[Config::clientMax];

      static const uint16_t messageMax = 128;
      static const uint16_t messageCapacity = 1024*20;
      typedef char MessageBuffer[messageCapacity];
      typedef uint16_t OffsetSet[messageMax];
      typedef uint16_t LengthSet[messageMax];

      struct {
        MessageBuffer buffers[Config::clientMax];
        OffsetSet offsetSets[Config::clientMax];
        LengthSet lengthSets[Config::clientMax];
      } messageData;
    }

    void initialize() {
      for(uint8_t i=0; i<Config::clientMax; ++i) {
        Carrying::messageBuffers[i].configure(
          Carrying::messageData.offsetSets[i],
          Carrying::messageData.lengthSets[i],
          Carrying::messageMax,
          Carrying::messageData.buffers[i],
          Carrying::messageCapacity
        );
      }
    }

    void create(Piper::ClientID piperID) {
      assert(count != Config::clientMax);

      indicesByPiperIDs[piperID] = count;
      ClientID id = idPool.obtain();
      indices[id] = count;
      ids[count] = id;
      piperIDs[count] = piperID;
      sendCounts[count] = 0;
      PingPong::timeouts[count] = 0;
      PingPong::nextIDs[count] = 0;
      count++;


      // dummy:
      char test[] = { static_cast<char>(MessageType::Test) };
      Carrier::send(id, test, 1, 30);
    }

    uint8_t getCount() {
      return count;
    }

    ClientID findIDByPiperID(Piper::ClientID piperID) {
      uint8_t index = indicesByPiperIDs[piperID];
      return ids[index];
    }

    bool locatePiperID(Piper::ClientID id) {
      return indicesByPiperIDs[id] != -1;
    }

    void clearSendCounts() {
      memset(sendCounts, 0, sizeof(sendCounts));
    }
  }
}
