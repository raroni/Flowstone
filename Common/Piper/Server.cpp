#include "SysNet/SysNet.h"
#include "Common/Piper/Transmission.h"
#include "Common/Piper/Server.h"

namespace Piper {
  Server::Server() :
  inBuffer(
    Config::Server::inMessageMax,
    Config::Server::inMessageCapacity,
    inData.ids,
    inData.offsets,
    inData.lengths,
    inData.storage
  ) {
    socket = SysNet::createSocket();
  }

  void Server::listen(const Address &address) {
    SysNet::bind(socket, address);
  }

  bool Server::findClientID(const Address &address, ClientID &id) {
    for(uint8_t i=0; i<clientCount; ++i) {
      if(SysNet::addressEqual(addresses[i], address)) {
        id = ids[i];
        return true;
      }
    }
    return false;
  }

  void Server::poll() {
    Packet packet;
    ClientID id;
    while(true) {
      bool result = Transmission::receive(socket, packet);
      if(!result) {
        return;
      }
      if(!findClientID(packet.address, id)) {
        if(clientCount == Config::Server::clientMax) {
          continue;
        }
        id = idPool.obtain();
        ids[clientCount] = id;
        addresses[clientCount] = packet.address;
        clientCount++;
      }
      // handle ackStart, ackBits
      inBuffer.write(id, packet.message, packet.messageLength);
    }
  }

  void Server::clear() {
    inBuffer.clear();
    inBufferPosition = 0;
  }

  bool Server::readMessage(ClientID *id, const void **message, uint16_t *messageLength) {
    *messageLength = inBuffer.read(inBufferPosition++, id, message);
    return *messageLength != 0;
  }

  void Server::dispatch() {

  }
}
