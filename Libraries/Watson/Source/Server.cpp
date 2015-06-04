#include <assert.h>
#include "Watson/Server.h"

namespace Watson {
  namespace Server {
    ServerFunction functions[Config::boardKeyMax] = { NULL };

    void configure(uint8_t boardKey, ServerFunction function) {
      functions[boardKey] = function;
    }

    void request(uint8_t boardKey, const void *requestData, ResponseBuffer *responseBuffer) {
      ServerFunction func = functions[boardKey];
      assert(func != NULL);
      func(requestData, responseBuffer);
    }
  }
}
