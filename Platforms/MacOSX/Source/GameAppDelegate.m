#import "MacOSX/Util.h"
#import "MacOSX/GameAppDelegate.h"

@implementation GameAppDelegate

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender {
  requestTermination();
  return NSTerminateCancel;
}

@end
