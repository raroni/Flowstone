#ifndef SERVER_GAME_CLIENT_SET_H
#define SERVER_GAME_CLIENT_SET_H

#include "Common/Piper/Config.h"
#include "ServerGame/ServerGameConfig.h"
#include "Common/Piper/ClientID.h"
#include "ServerGame/ServerGameClientID.h"

namespace ServerGameClientSet {
  extern int8_t indicesByPiperIDs[Piper::Config::Server::clientMax];
  extern uint8_t indices[ServerGameConfig::clientMax];
  extern ServerGameClientID ids[ServerGameConfig::clientMax];
  extern Piper::ClientID piperIDs[ServerGameConfig::clientMax];
  extern uint8_t sendCounts[ServerGameConfig::clientMax];

  void create(Piper::ClientID piperID);
  ServerGameClientID findIDByPiperID(Piper::ClientID piperID);
  void clearSendCounts();
  bool locatePiperID(Piper::ClientID id);
  uint8_t getCount();
}

#endif
