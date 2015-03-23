#include <assert.h>
#include <string.h>
#include "ServerGame/ServerGameClientIDPool.h"
#include "ServerGame/ServerGameClientSet.h"

namespace ServerGameClientSet {
  static ServerGameClientIDPool idPool;

  int8_t indicesByPiperIDs[Piper::Config::Server::clientMax] = { -1 };
  uint8_t indices[ServerGameConfig::clientMax];
  ServerGameClientID ids[ServerGameConfig::clientMax];
  Piper::ClientID piperIDs[ServerGameConfig::clientMax];
  uint8_t sendCounts[ServerGameConfig::clientMax];
  uint32_t rtts[ServerGameConfig::clientMax];
  uint8_t count = 0;

  namespace PingPong {
    StartTimeSet startTimes[ServerGameConfig::clientMax];
    double timeouts[ServerGameConfig::clientMax];
    uint8_t nextIDs[ServerGameConfig::clientMax];
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
