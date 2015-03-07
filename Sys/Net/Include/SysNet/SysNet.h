#ifndef SYSNET_H

#include <stddef.h>
#include "SysNet/Packet.h"
#include "SysNet/Socket.h"

namespace SysNet {
  Socket createSocket();
  void send(Socket socket, const Packet &packet);
  bool receive(Socket socket, Packet &packet);
}

#endif
