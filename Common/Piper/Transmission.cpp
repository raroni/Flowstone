#include "SysNet/SysNet.h"
#include "Common/Piper/Transmission.h"

namespace Piper {
  namespace Transmission {
    static const size_t bufferSize = 1024*20;
    char buffer[bufferSize];

    void send(Socket socket, const Packet &packet) {
      //uint16_t length = 1234;

      // setup buffer

      /*
      SysNet::send(
        socket,
        packet.address,
        buffer,
        length
      );
      */
    }

    void receive(Socket socket, Packet &packet) {
      // receive(socket, Address &address, buffer, bufferSize);
      // handle return
    }
  }
}
