#include <stddef.h>
#include "ClientPlatform.h"
#include "SysTime/SysTime.h"
#include "PresentationSync.h"
#include "Presentation.h"
#include "UserGame.h"

namespace Presentation {
  using namespace PresentationSync;

  void* run(void *data) {
    while(!UserGame::shouldTerminate()) {
      if(shouldPresent()) {
        ClientPlatform::present();
        handlePresentationCompletion();
      } else {
        SysTime::sleep(1000);
      }
    }
    return NULL;
  }
}
