#include <string.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>
#include "Common/Error.h"
#include "SysNet/SysNet.h"

namespace SysNet {
  static sockaddr sockAddress;
  static socklen_t addressLength;
  static const size_t bufferSize = 10*1024;
  static char buffer[bufferSize];

  Socket createSocket() {
    Socket s = socket(AF_INET, SOCK_DGRAM, 0);
    fcntl(s, F_SETFL, O_NONBLOCK);
    return s;
  }

  void bind(Socket socket, const Address &address) {
    memset(&sockAddress, 0, sizeof(sockAddress));
    sockaddr_in *ipv4Address = reinterpret_cast<sockaddr_in*>(&sockAddress);
    ipv4Address->sin_family = AF_INET;
    ipv4Address->sin_addr.s_addr = *reinterpret_cast<const uint32_t*>(address.ip);
    ipv4Address->sin_port = htons(address.port);
    addressLength = sizeof(sockaddr_in);
    int bindResult = ::bind(socket, &sockAddress, addressLength);

    if(bindResult == -1) {
      fatalError("bind() failed.");
    }
  }

  void send(Socket socket, const Packet &packet) {
    memset(&sockAddress, 0, sizeof(sockAddress));
    sockaddr_in *ipv4Address = reinterpret_cast<sockaddr_in*>(&sockAddress);
    ipv4Address->sin_family = AF_INET;
    ipv4Address->sin_addr.s_addr = *reinterpret_cast<const uint32_t*>(packet.address.ip);
    ipv4Address->sin_port = htons(packet.address.port);

    addressLength = sizeof(sockaddr_in);

    ssize_t result = sendto(
      socket,
      packet.message,
      packet.messageLength,
      0,
      &sockAddress,
      addressLength
    );

    if(result == -1) {
      fatalError("sendto() failed.");
    }
  }

  bool receive(Socket socket, Packet &packet) {
    addressLength = sizeof(sockAddress);
    while(true) {
      ssize_t result = recvfrom(
        socket,
        buffer,
        bufferSize,
        0,
        &sockAddress,
        &addressLength
      );

      if(result == -1) {
        if(errno == EAGAIN) {
          return false;
        } else {
          fatalError("recvfrom() failed with unmanageable error.");
        }
      }

      if(sockAddress.sa_family != AF_INET) {
        continue;
      }

      sockaddr_in *ipv4Address = reinterpret_cast<sockaddr_in*>(&sockAddress);
      memcpy(packet.address.ip, &ipv4Address->sin_addr.s_addr, sizeof(uint8_t)*4);
      packet.address.port = ipv4Address->sin_port;
      packet.message = buffer;
      packet.messageLength = result;
      return true;
    }
  }
}
