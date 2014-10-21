#include "Bro/Bro.h"
#include "Bro/OSX/Window.h"
#include "Bro/OSX/WindowDelegate.h"
#include "Bro/OSX/View.h"

@interface BroAppDelegate : NSObject <NSApplicationDelegate>
@end

@implementation BroAppDelegate

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender {
  broRequestTermination();
  return NSTerminateCancel;
}

@end
