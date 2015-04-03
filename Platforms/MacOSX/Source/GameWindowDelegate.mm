#include "Client/Game.h"
#import "MacOSX/GameWindowDelegate.h"

@implementation GameWindowDelegate

- (BOOL)windowShouldClose:(id)sender {
    Client::Game::requestTermination();
    return NO;
}

@end
