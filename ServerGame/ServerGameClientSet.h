#ifndef SERVER_GAME_CLIENT_SET_H
#define SERVER_GAME_CLIENT_SET_H

#include "Common/GameTime.h"
#include "Common/Piper/Config.h"
#include "Common/Piper/Sequence.h"
#include "Common/LoopStream.h"
#include "ServerGame/ServerGameConfig.h"
#include "Common/Piper/ClientID.h"
#include "ServerGame/ServerGameClientID.h"

namespace ServerGameClientSet {
  extern int8_t indicesByPiperIDs[Piper::Config::Server::clientMax];
  extern uint8_t indices[ServerGameConfig::clientMax];
  extern ServerGameClientID ids[ServerGameConfig::clientMax];
  extern Piper::ClientID piperIDs[ServerGameConfig::clientMax];
  extern uint8_t sendCounts[ServerGameConfig::clientMax];
  extern uint32_t rtts[ServerGameConfig::clientMax];

  namespace PingPong {
    struct StartTimeSet {
      uint64_t list[UINT8_MAX];
    };

    extern StartTimeSet startTimes[ServerGameConfig::clientMax];
    extern double timeouts[ServerGameConfig::clientMax];
    extern uint8_t nextIDs[ServerGameConfig::clientMax];
  }

  namespace Carrying {
    const uint8_t max = 128;

    struct DurationSet {
      GameTime::MSecond16 durations[max];
    };
    struct TimeoutSet {
      float timeouts[max];
    };
    struct HandleSet {
      uint16_t handles[max];
    };
    struct PiperIDSet {
      Piper::Sequence ids[max];
    };

    extern uint8_t counts[ServerGameConfig::clientMax];
    extern DurationSet durationSets[ServerGameConfig::clientMax];
    extern TimeoutSet timeoutSets[ServerGameConfig::clientMax];
    extern HandleSet handleSets[ServerGameConfig::clientMax];
    extern PiperIDSet piperIDSets[ServerGameConfig::clientMax];
    extern LoopStream messageBuffers[ServerGameConfig::clientMax];
  }

  void initialize();
  void create(Piper::ClientID piperID);
  ServerGameClientID findIDByPiperID(Piper::ClientID piperID);
  void clearSendCounts();
  bool locatePiperID(Piper::ClientID id);
  uint8_t getCount();
}

#endif
