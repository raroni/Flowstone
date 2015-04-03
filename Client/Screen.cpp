#include <stddef.h>
#include "SysTime/SysTime.h"
#include "Client/ScreenSync.h"
#include "Client/Screen.h"
#include "Client/Platform.h"
#include "Client/Game.h"

namespace Client {
  namespace Screen {
    using namespace ScreenSync;

    void* run(void *data) {
      while(!Client::Game::shouldTerminate()) {
        if(shouldPresent()) {
          Platform::present();
          handlePresentationCompletion();
        } else {
          SysTime::sleep(1000);
        }
      }
      return NULL;
    }
  }
}
