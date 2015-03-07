#include <assert.h>
#include <string.h>
#include "SysNet/SysNet.h"
#include "Common/Piper/Transmission.h"

namespace Piper {
  namespace Transmission {
    static const size_t bufferSize = 1024*20;
    char buffer[bufferSize];
    const static uint8_t headerSize = sizeof(uint16_t)*2+sizeof(BitSet32);

    void send(Socket socket, const Packet &packet) {
      uint16_t *uint16View = reinterpret_cast<uint16_t*>(buffer);
      uint16View[0] = packet.id;
      uint16View[1] = packet.ackStart;
      memcpy(buffer+5, &packet.ackBits, sizeof(BitSet32));
      assert(headerSize + packet.messageLength <= bufferSize);
      memcpy(buffer+headerSize, packet.message, packet.messageLength);

      SysNet::Packet sysNetPacket;
      sysNetPacket.address = packet.address;
      sysNetPacket.message = buffer;
      sysNetPacket.messageLength = headerSize+packet.messageLength;

      SysNet::send(socket, sysNetPacket);
    }

    bool receive(Socket socket, Packet &packet) {
      SysNet::Packet sysNetPacket;
      if(SysNet::receive(socket, sysNetPacket)) {
        const uint16_t *uint16View = static_cast<const uint16_t*>(sysNetPacket.message);
        const char *charView = static_cast<const char*>(sysNetPacket.message);

        packet.address = sysNetPacket.address;
        packet.id = uint16View[0];
        packet.ackStart = uint16View[1];
        memcpy(&packet.ackBits, charView+sizeof(uint16_t)*2, sizeof(BitSet32));
        packet.message = charView+headerSize;
        packet.messageLength = sysNetPacket.messageLength;
        return true;
      } else {
        return false;
      }
    }
  }
}
