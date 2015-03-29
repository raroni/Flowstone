#include "UserGame.h"
#import "MacOSX/GameWindowDelegate.h"

@implementation GameWindowDelegate

- (BOOL)windowShouldClose:(id)sender {
    UserGame::requestTermination();
    return NO;
}

@end
