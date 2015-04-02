#ifndef PRESENTATION_SYNC_H
#define PRESENTATION_SYNC_H

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

#endif
