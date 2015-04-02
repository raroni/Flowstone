#include <assert.h>
#include <string.h>
#include "Server/ServerGameClientIDPool.h"
#include "Server/ServerGameClientSet.h"

// dummy:
#include "Server/ServerCarrier.h"
#include "Common/MessageType.h"

namespace ServerGameClientSet {
  static ServerGameClientIDPool idPool;

  int8_t indicesByPiperIDs[Piper::Config::Server::clientMax] = { -1 };
  uint8_t indices[ServerGameConfig::clientMax];
  ServerGameClientID ids[ServerGameConfig::clientMax];
  Piper::ClientID piperIDs[ServerGameConfig::clientMax];
  uint8_t sendCounts[ServerGameConfig::clientMax];
  SysTime::MSecond16 rtts[ServerGameConfig::clientMax] = { 250 };
  uint8_t count = 0;

  namespace PingPong {
    StartTimeSet startTimes[ServerGameConfig::clientMax];
    double timeouts[ServerGameConfig::clientMax];
    uint8_t nextIDs[ServerGameConfig::clientMax];
  }

  namespace Carrying {
    uint8_t counts[ServerGameConfig::clientMax];
    DurationSet durationSets[ServerGameConfig::clientMax];
    TimeoutSet timeoutSets[ServerGameConfig::clientMax];
    HandleSet handleSets[ServerGameConfig::clientMax];
    PiperIDSet piperIDSets[ServerGameConfig::clientMax];
    LoopStream messageBuffers[ServerGameConfig::clientMax];

    static const uint16_t messageMax = 128;
    static const uint16_t messageCapacity = 1024*20;
    typedef char MessageBuffer[messageCapacity];
    typedef uint16_t OffsetSet[messageMax];
    typedef uint16_t LengthSet[messageMax];

    struct {
      MessageBuffer buffers[ServerGameConfig::clientMax];
      OffsetSet offsetSets[ServerGameConfig::clientMax];
      LengthSet lengthSets[ServerGameConfig::clientMax];
    } messageData;
  }

  void initialize() {
    for(uint8_t i=0; i<ServerGameConfig::clientMax; ++i) {
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
    assert(count != ServerGameConfig::clientMax);

    indicesByPiperIDs[piperID] = count;
    ServerGameClientID id = idPool.obtain();
    indices[id] = count;
    ids[count] = id;
    piperIDs[count] = piperID;
    sendCounts[count] = 0;
    PingPong::timeouts[count] = 0;
    PingPong::nextIDs[count] = 0;
    count++;


    // dummy:
    char test[] = { static_cast<char>(MessageType::Test) };
    ServerCarrier::send(id, test, 1, 30);
  }

  uint8_t getCount() {
    return count;
  }

  ServerGameClientID findIDByPiperID(Piper::ClientID piperID) {
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
