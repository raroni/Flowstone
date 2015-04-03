#ifndef CLIENT_SCREEN_SYNC_H
#define CLIENT_SCREEN_SYNC_H

namespace Client {
  namespace ScreenSync {
    enum State {
      AwaitingDraw,
      AwaitingPresentation
    };

    void initialize();
    void terminate();
    bool shouldPresent();
    bool shouldDraw();
    void handleDrawCompletion();
    void handlePresentationCompletion();
  }
}

#endif
