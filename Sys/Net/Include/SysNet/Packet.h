#ifndef SYSNET_PACKET_H
#define SYSNET_PACKET_H

#include <stdint.h>
#include "SysNet/Address.h"

namespace SysNet {
  struct Packet {
    Address address;
    const void *message;
    uint16_t messageLength;
  };
}

#endif
