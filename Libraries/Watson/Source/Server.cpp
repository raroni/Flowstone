#include "Watson/Server.h"

namespace Watson {
  namespace Server {
    ServerFunction functions[Config::boardKeyMax];

    void configure(uint8_t boardKey, ServerFunction function) {
      functions[boardKey] = function;
    }
  }
}
