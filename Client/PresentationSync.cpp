#include <assert.h>
#include "SysThread.h"
#include "PresentationSync.h"

namespace Client {
  namespace PresentationSync {
    State state;
    SysThread::Mutex mutex;

    State getState() {
      SysThread::lock(&mutex);
      State copy = state;
      SysThread::unlock(&mutex);
      return copy;
    }

    void setState(State newState) {
      SysThread::lock(&mutex);
      state = newState;
      SysThread::unlock(&mutex);
    }

    void initialize() {
      state = AwaitingDraw;
      SysThread::initMutex(&mutex);
    }

    void terminate() {
      SysThread::destroyMutex(&mutex);
    }

    bool shouldPresent() {
      return getState() == AwaitingPresentation;
    }

    bool shouldDraw() {
      return getState() == AwaitingDraw;
    }

    void handleDrawCompletion() {
      assert(getState() == AwaitingDraw);
      setState(AwaitingPresentation);
    }

    void handlePresentationCompletion() {
      assert(getState() == AwaitingPresentation);
      setState(AwaitingDraw);
    }

    bool needsDraw() {
      return getState() == AwaitingDraw;
    }
  }
}
