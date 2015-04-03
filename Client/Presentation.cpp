#include <stddef.h>
#include "SysTime/SysTime.h"
#include "Client/PresentationSync.h"
#include "Client/Presentation.h"
#include "Client/Platform.h"
#include "Client/Game.h"

namespace Client {
  namespace Presentation {
    using namespace PresentationSync;

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
