#include "Watson/ServerFunction.h"
#include "Watson/Server.h"
#include "Behavior/BoardKey.h"
#include "Behavior/Server.h"

namespace Behavior {
  namespace Server {
    typedef Watson::Board Board;
    typedef Watson::ResponseBuffer ResponseBuffer;
    typedef Watson::ServerFunction ServerFunction;

    void setupType(BoardKey key, ServerFunction function) {
      uint8_t keyInt = static_cast<uint8_t>(key);
      Watson::Server::configure(keyInt, function);
    }

    void checkThreat(const void *request, ResponseBuffer *response) {
      bool value = false;
      response->set(&value, sizeof(bool));
    }

    void checkWood(const void *request, ResponseBuffer *response) {
      bool value = false;
      response->set(&value, sizeof(bool));
    }

    void setup() {
      setupType(BoardKey::IsThreatened, checkThreat);
      setupType(BoardKey::HasWood, checkWood);
    }
  }
}
