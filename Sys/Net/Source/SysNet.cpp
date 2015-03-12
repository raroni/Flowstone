#include <string.h>
#include "SysNet/SysNet.h"

namespace SysNet {
  bool addressEqual(const Address &a, const Address &b) {
    return memcmp(&a, &b, sizeof(Address)) == 0;
  }
}
