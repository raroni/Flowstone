#include <OpenGL/gl3.h>
#include "Bro/OSX/View.h"
#include "Bro/Bro.h"

@class NSOpenGLPixelFormat;

@implementation BroView

static BroKey convertKeyCode(unsigned short keyCode) {
  if(keyCode > 127) return BroKeyUnknown;

  static const BroKey table[] = {
    BroKeyA,
    BroKeyS,
    BroKeyD,
    BroKeyF,
    BroKeyH,
    BroKeyG,
    BroKeyZ,
    BroKeyX,
    BroKeyC,
    BroKeyV,
    BroKeyUnknown,
    BroKeyB,
    BroKeyQ,
    BroKeyW,
    BroKeyE,
    BroKeyR,
    BroKeyY,
    BroKeyT,
    BroKey1,
    BroKey2,
    BroKey3,
    BroKey4,
    BroKey6,
    BroKey5,
    BroKeyUnknown,
    BroKey9,
    BroKey7,
    BroKeyUnknown,
    BroKey8,
    BroKey0,
    BroKeyUnknown,
    BroKeyO,
    BroKeyU,
    BroKeyUnknown,
    BroKeyI,
    BroKeyP,
    BroKeyEnter,
    BroKeyL,
    BroKeyJ,
    BroKeyUnknown,
    BroKeyK,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyComma,
    BroKeyUnknown,
    BroKeyN,
    BroKeyM,
    BroKeyPeriod,
    BroKeyTab,
    BroKeySpace,
    BroKeyUnknown,
    BroKeyBackspace,
    BroKeyUnknown,
    BroKeyEscape,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyCapslock,
    BroKeyLeftAlt,
    BroKeyLeftControl,
    BroKeyRightShift,
    BroKeyRightAlt,
    BroKeyRightControl,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyUnknown,
    BroKeyLeft,
    BroKeyRight,
    BroKeyDown,
    BroKeyUp,
    BroKeyUnknown
  };

  return table[keyCode];
}

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
  BroKey key = convertKeyCode([event keyCode]);
  if(!event.ARepeat) {
    broHandleKeyDown(key);
  }
}

- (void)keyUp:(NSEvent*)event {
  BroKey key = convertKeyCode([event keyCode]);
  if(!event.ARepeat) {
    broHandleKeyUp(key);
  }
}

@end
