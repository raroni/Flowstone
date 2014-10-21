#include "Bro/Bro.h"

@interface BroWindowDelegate : NSObject <NSWindowDelegate>
@end

@implementation BroWindowDelegate

- (BOOL)windowShouldClose:(id)sender {
    broRequestTermination();
    return NO;
}

@end
