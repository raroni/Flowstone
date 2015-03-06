#ifndef PIPER_CLIENT_H
#define PIPER_CLIENT_H

#include "Common/Piper/Address.h"

namespace Piper {
  class Client {
  public:
    void setAddress(Address address);
  private:
    Address serverAddress;
  };
}

#endif
