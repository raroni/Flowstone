#include "Watson/ServerFunction.h"
#include "Watson/Server.h"
#include "AI/BoardKey.h"
#include "AI/Server.h"

namespace AI {
  namespace Server {
    typedef Watson::Board Board;
    typedef Watson::Request Request;

    void setupType(BoardKey key, Watson::ServerFunction function) {
      uint8_t keyInt = static_cast<uint8_t>(key);
      Watson::Server::configure(keyInt, function);
    }

    void testLoader(const Request *request, Board *board) {

    }

    void setup() {
      setupType(BoardKey::PLACEHOLDER, testLoader);
    }
  }
}
