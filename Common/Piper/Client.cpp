#include "SysNet/SysNet.h"
#include "Common/Piper/Transmission.h"
#include "Common/Piper/Client.h"

namespace Piper {
  Client::Client() {
    socket = SysNet::createSocket();
  }

  void Client::setAddress(Address address) {
    serverAddress = address;
  }

  bool Client::receive(Packet &packet) {
    return Transmission::receive(socket, packet);
  }

  void Client::send(const Packet &packet) {
    Transmission::send(socket, packet);
  }
}
