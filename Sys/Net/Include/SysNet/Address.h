#ifndef SYSNET_ADDRESS_H
#define SYSNET_ADDRESS_H

#include <stdint.h>

namespace SysNet {
  struct Address {
    uint8_t ip[4];
    uint16_t port;
  };
}

#endif
