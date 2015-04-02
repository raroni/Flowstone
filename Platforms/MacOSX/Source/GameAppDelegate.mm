#include "Client/Game.h"
#import "MacOSX/GameAppDelegate.h"

@implementation GameAppDelegate

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender {
  Client::Game::requestTermination();
  return NSTerminateCancel;
}

@end
