#include <OpenGL/gl3.h>
#include "GameView.h"

@class NSOpenGLPixelFormat;

@implementation GameView

- (BOOL)isOpaque {
  return YES;
}

- (BOOL)canBecomeKeyView {
  return YES;
}

- (BOOL)acceptsFirstResponder {
  return YES;
}

- (void)keyDown:(NSEvent *)event {
  if(!event.ARepeat) {
    NSLog(@"Handle key down somehow.");
  }
}

- (void)keyUp:(NSEvent*)event {
  if(!event.ARepeat) {
    NSLog(@"Handle key up somehow.");
  }
}

@end
