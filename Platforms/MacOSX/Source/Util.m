#import "MacOSX/Util.h"

BOOL shouldTerminate = NO;

void requestTermination() {
  shouldTerminate = YES;
}
