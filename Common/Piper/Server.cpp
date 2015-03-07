#include "SysNet/SysNet.h"
#include "Common/Piper/Transmission.h"
#include "Common/Piper/Server.h"

namespace Piper {
  Server::Server() {
    socket = SysNet::createSocket();
  }

  void Server::listen(const Address &address) {
    SysNet::bind(socket, address);
  }

  bool Server::receive(Packet &packet) {
    return Transmission::receive(socket, packet);
  }
}
