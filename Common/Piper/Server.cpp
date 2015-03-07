#include "SysNet/SysNet.h"
#include "Common/Piper/Server.h"

namespace Piper {
  Server::Server() {
    socket = SysNet::createSocket();
  }

  void Server::listen(const Address &address) {
    SysNet::bind(socket, address);
  }
}
