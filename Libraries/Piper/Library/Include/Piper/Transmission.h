#ifndef PIPER_TRANSMISSION_H
#define PIPER_TRANSMISSION_H

#include "Piper/Packet.h"
#include "Piper/Socket.h"

namespace Piper {
  namespace Transmission {
    void send(Socket socket, const Packet &packet);
    bool receive(Socket socket, Packet &packet);
  }
}

#endif
