#ifndef SYSNET_H

#include <stddef.h>
#include "SysNet/Address.h"
#include "SysNet/Socket.h"

namespace SysNet {
  Socket createSocket();
  void send(Socket socket, const Address &address, const void *buffer, size_t bufferLength);
  bool receive(Socket socket, Address &address, void *buffer, size_t bufferSize);
}

#endif
