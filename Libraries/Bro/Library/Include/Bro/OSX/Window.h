#ifndef BRO_BRO_WINDOW_H
#define BRO_BRO_WINDOW_H

@interface BroWindow : NSWindow {}
@end

@implementation BroWindow

- (BOOL)canBecomeKeyWindow {
  return YES;
}

@end

#endif
