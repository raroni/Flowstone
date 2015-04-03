#ifndef SERVER_CLIENT_SET_H
#define SERVER_CLIENT_SET_H

#include "Misc/GameTime.h"
#include "Piper/Config.h"
#include "Piper/Sequence.h"
#include "Misc/LoopStream.h"
#include "Server/Config.h"
#include "Piper/ClientID.h"
#include "Server/ClientID.h"

namespace Server {
  namespace ClientSet {
    extern int8_t indicesByPiperIDs[Piper::Config::Server::clientMax];
    extern uint8_t indices[Config::clientMax];
    extern ClientID ids[Config::clientMax];
    extern Piper::ClientID piperIDs[Config::clientMax];
    extern uint8_t sendCounts[Config::clientMax];
    extern SysTime::MSecond16 rtts[Config::clientMax];

    namespace PingPong {
      struct StartTimeSet {
        SysTime::MSecond32 list[UINT8_MAX];
      };

      extern StartTimeSet startTimes[Config::clientMax];
      extern double timeouts[Config::clientMax];
      extern uint8_t nextIDs[Config::clientMax];
    }

    namespace Carrying {
      const uint8_t max = 128;

      struct DurationSet {
        SysTime::MSecond16 durations[max];
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

      extern uint8_t counts[Config::clientMax];
      extern DurationSet durationSets[Config::clientMax];
      extern TimeoutSet timeoutSets[Config::clientMax];
      extern HandleSet handleSets[Config::clientMax];
      extern PiperIDSet piperIDSets[Config::clientMax];
      extern LoopStream messageBuffers[Config::clientMax];
    }

    void initialize();
    void create(Piper::ClientID piperID);
    ClientID findIDByPiperID(Piper::ClientID piperID);
    void clearSendCounts();
    bool locatePiperID(Piper::ClientID id);
    uint8_t getCount();
  }
}

#endif
