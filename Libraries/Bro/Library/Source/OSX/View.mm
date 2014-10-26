#include <OpenGL/gl3.h>
#include "Bro/OSX/View.h"

@class NSOpenGLPixelFormat;

@implementation BroView

- (BOOL)isOpaque {
    return YES;
}

- (BOOL)canBecomeKeyView {
    return YES;
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

@end
