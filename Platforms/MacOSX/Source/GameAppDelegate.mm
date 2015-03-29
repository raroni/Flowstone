#include "UserGame.h"
#import "MacOSX/GameAppDelegate.h"

@implementation GameAppDelegate

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender {
  UserGame::requestTermination();
  return NSTerminateCancel;
}

@end
