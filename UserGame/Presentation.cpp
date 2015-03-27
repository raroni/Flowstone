#include "Platform.h"
#include "SysTime/SysTime.h"
#include "UserGame.h"
#include "PresentationSync.h"
#include "Presentation.h"

namespace Presentation {
  using namespace PresentationSync;

  void* run(void *data) {
    while(!UserGame::shouldTerminate()) {
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
