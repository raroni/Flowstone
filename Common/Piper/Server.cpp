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

  bool Server::findClientID(const Address &address, ClientID &id) {
    for(uint8_t i=0; i<clientCount; ++i) {
      if(SysNet::addressEqual(addresses[i], address)) {
        id = ids[i];
        return true;
      }
    }
    return false;
  }

  Sequence Server::createSequenceID(ClientID id) {
    uint8_t index = indices[id];
    return nextSequenceIDs[index]++;
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
        indices[id] = clientCount;
        nextSequenceIDs[clientCount] = 0;
        clientCount++;
      }

      uint8_t index = indices[id];
      AckSet128 &outAckSet128 = outAcks[index];
      outAckSet128.ack(packet.ackHead);
      for(uint8_t i=0; i<32; ++i) {
        if(packet.ackBits.get(i)) {
          outAckSet128.ack(packet.ackHead-1-i);
        }
      }

      AckSet32 &inAckSet = inAcks[index];
      inAckSet.ack(packet.id);
      inBuffer.write(id, packet.message, packet.messageLength);
    }
  }

  Sequence Server::sendMessage(ClientID clientID, const void *message, uint16_t messageLength) {
    Sequence sequenceID = createSequenceID(clientID);
    outBuffer.write(
      clientID,
      sequenceID,
      message,
      messageLength
    );
    return sequenceID;
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
    Packet packet;
    ClientID clientID;
    Sequence sequenceID;
    const void *message;
    uint16_t messageLength;

    for(uint16_t p = 0; p<outBuffer.getCount(); ++p) {
      outBuffer.read(p, &clientID, &sequenceID, &message, &messageLength);

      uint8_t index = indices[clientID];
      const AckSet32 &acks = inAcks[index];
      packet.address = addresses[index];
      packet.id = sequenceID;
      packet.ackHead = acks.getHead();
      memcpy(&packet.ackBits, reinterpret_cast<const char*>(&acks.getBits()), 4);
      packet.message = message;
      packet.messageLength = messageLength;
      Transmission::send(socket, packet);
    }

    outBuffer.clear();
  }
}
