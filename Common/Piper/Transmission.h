#ifndef PIPER_TRANSMISSION_H
#define PIPER_TRANSMISSION_H

#include "Common/Piper/Packet.h"
#include "Common/Piper/Socket.h"

namespace Piper {
  void send(Socket socket, const Packet &packet);
  void receive(Socket socket, Packet &packet);
}

#endif
