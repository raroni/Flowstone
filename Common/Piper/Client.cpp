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

  uint16_t Client::createID() {
    return nextID++;
  }

  void Client::poll() {
    Packet packet;
    while(true) {
      bool result = Transmission::receive(socket, packet);
      if(!result) {
        return;
      }
      if(!SysNet::addressEqual(packet.address, serverAddress)) {
        continue;
      }

      // do something with ackStart, ackBits
      inBuffer.write(packet.message, packet.messageLength);
    }
  }

  bool Client::readMessage(const void **message, uint16_t *messageLength) {
    *messageLength = inBuffer.read(inBufferPosition++, message);
    return *messageLength != 0;
  }

  void Client::clear() {
    inBuffer.clear();
    inBufferPosition = 0;
  }

  void Client::sendMessage(Sequence id, const void *message, uint16_t messageLength) {
    outBuffer.write(message, messageLength);
    outIDs[outBuffer.getCount()-1] = id;
  }

  void Client::dispatch() {
    Packet packet;
    uint16_t position = 0;
    uint16_t messageLength;
    const void *message = nullptr;
    for(uint16_t p = 0; p<outBuffer.getCount(); ++p) {
      messageLength = outBuffer.read(p, &message);
      packet.address = serverAddress;
      packet.id = outIDs[position];
      // todo
      // packet.ackStart = ackStart;
      // packet.ackBits = ackBits;
      packet.message = message;
      packet.messageLength = messageLength;
      Transmission::send(socket, packet);
    }
    outBuffer.clear();
  }
}
