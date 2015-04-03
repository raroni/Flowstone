#ifndef CLIENT_PRESENTATION_SYNC_H
#define CLIENT_PRESENTATION_SYNC_H

namespace Client {
  namespace PresentationSync {
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
