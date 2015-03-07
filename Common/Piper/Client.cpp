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

  bool Client::receive(
    Sequence &id,
    Sequence &ackStart,
    BitSet32 &ackBits,
    const void *message,
    uint16_t messageLength
  ) {
    Packet packet;
    while(true) {
      if(Transmission::receive(socket, packet)) {
        if(SysNet::addressEqual(packet.address, serverAddress)) {
          id = packet.id;
          ackStart = packet.ackStart;
          ackBits = packet.ackBits;
          message = packet.message;
          messageLength = packet.messageLength;
          return true;
        } else {
          continue;
        }
      } else {
        return false;
      }
    }
  }

  void Client::send(
    Sequence id,
    Sequence ackStart,
    const BitSet32 &ackBits,
    const void *message,
    uint16_t messageLength
  ) {
    Packet packet;
    packet.address = serverAddress;
    packet.id = id;
    packet.ackStart = ackStart;
    packet.ackBits = ackBits;
    packet.message = message;
    packet.messageLength = messageLength;
    Transmission::send(socket, packet);
  }
}
