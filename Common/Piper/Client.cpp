#include "SysNet/SysNet.h"
#include "Common/Piper/AckStatus.h"
#include "Common/Piper/Transmission.h"
#include "Common/Piper/Client.h"

namespace Piper {
  Client::Client() :
  inBuffer(
    Config::Client::inMessageMax,
    Config::Client::inMessageCapacity,
    inData.offsets,
    inData.lengths,
    inData.storage
  ) {
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

      if(inAcks.getStatus(packet.id) == AckStatus::No) {
        inAcks.ack(packet.id);
        inBuffer.write(packet.message, packet.messageLength);
      }

      outAcks.ack(packet.ackStart);
      for(uint8_t i=0; i<32; ++i) {
        if(packet.ackBits.get(i)) {
          outAcks.ack(packet.ackStart+1+i);
        }
      }
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
    outBuffer.write(id, message, messageLength);
  }

  void Client::dispatch() {
    Packet packet;
    uint16_t messageLength;
    Sequence id;
    const void *message = nullptr;
    for(uint16_t p = 0; p<outBuffer.getCount(); ++p) {
      messageLength = outBuffer.read(p, &id, &message);
      packet.address = serverAddress;
      packet.id = id;
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