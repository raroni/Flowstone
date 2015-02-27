#import "MacOSX/Util.h"
#import "MacOSX/GameWindowDelegate.h"

@implementation GameWindowDelegate

- (BOOL)windowShouldClose:(id)sender {
    requestTermination();
    return NO;
}

@end
