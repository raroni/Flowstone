#include <stddef.h>
#include "ClientPlatform.h"
#include "SysTime/SysTime.h"
#include "PresentationSync.h"
#include "Presentation.h"
#include "ClientGame.h"

namespace Presentation {
  using namespace PresentationSync;

  void* run(void *data) {
    while(!ClientGame::shouldTerminate()) {
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
