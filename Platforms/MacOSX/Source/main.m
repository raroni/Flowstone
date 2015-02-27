#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import "MacOSX/GameView.h"

@interface GameWindow : NSWindow {}
@end

NSAutoreleasePool *autoreleasePool;
static BOOL shouldTerminate = NO;
static id appDelegate;
static GameWindow *window;
static GameView *view;
static id windowDelegate;
static NSOpenGLContext *context;

static void fatalError(NSString *message) {
  NSLog(@"Mac OSX system error: %@\n", message);
  exit(1);
}

static void requestTermination() {
  shouldTerminate = YES;
}

static void handleSigint(int signum) {
  requestTermination();
}

static void setupMenu() {
  NSMenu *menu = [[NSMenu alloc] init];
  NSMenuItem *quitItem = [[NSMenuItem alloc] initWithTitle:@"Quit" action:@selector(terminate:) keyEquivalent:@"q"];
  [menu addItem:quitItem];

  NSMenuItem *barItem = [[NSMenuItem alloc] init];
  [barItem setSubmenu: menu];

  NSMenu *bar = [[NSMenu alloc] init];
  [bar addItem: barItem];
  [NSApp setMainMenu:bar];
}

@interface GameApplication : NSApplication
@end

@implementation GameApplication
@end

@interface GameAppDelegate : NSObject <NSApplicationDelegate>
@end

@implementation GameAppDelegate

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender {
  requestTermination();
  return NSTerminateCancel;
}

@end

@implementation GameWindow

- (BOOL)canBecomeKeyWindow {
  return YES;
}

@end

@interface GameWindowDelegate : NSObject <NSWindowDelegate>
@end

@implementation GameWindowDelegate

- (BOOL)windowShouldClose:(id)sender {
    requestTermination();
    return NO;
}

@end

static void createWindow() {
  unsigned int styleMask = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask;

  window = [[GameWindow alloc] initWithContentRect:NSMakeRect(0, 0, 800, 600)
                                                 styleMask:styleMask
                                                   backing:NSBackingStoreBuffered
                                                     defer:NO];
  if(window == nil) {
    fatalError(@"Could not create window.");
  }

  window.title = [NSString stringWithUTF8String:"Hi"];
  windowDelegate = [[GameWindowDelegate alloc] init];
  window.delegate = windowDelegate;

  // check whether you actually NEED to send bounds (maybe just send window, see glfw)
  NSView *contentView = window.contentView;
  view = [[GameView alloc] initWithFrame:contentView.bounds];
  window.contentView = view;

  [window center];
  [window makeKeyAndOrderFront:nil];
}

static void createContext() {
  NSOpenGLPixelFormatAttribute attributes[] = {
    NSOpenGLPFADoubleBuffer,
    NSOpenGLPFAOpenGLProfile,
    NSOpenGLProfileVersion3_2Core,
    0
  };
  NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
  if(pixelFormat == nil) {
    fatalError(@"Could not create pixel format.");
  }

  context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];

  GLint sync = 1;
  [context setValues:&sync forParameter:NSOpenGLCPSwapInterval];

  [pixelFormat release];
}

static void pollEvents() {
  while(true) {
    NSEvent *event = [NSApp nextEventMatchingMask:NSAnyEventMask
                                        untilDate:[NSDate distantPast]
                                           inMode:NSDefaultRunLoopMode
                                          dequeue:YES];
    if(event == nil) {
      return;
    }
    [NSApp sendEvent:event];
  }
}

static void terminate() {
  [context release];

  window.contentView = nil;
  [view release];

  [windowDelegate release];
  window.delegate = nil;

  [window release];

  [NSApp setDelegate:nil];
  [appDelegate release];

  [autoreleasePool release];
}

static void initialize() {
  autoreleasePool = [[NSAutoreleasePool alloc] init];

  CFBundleRef openglFramework = CFBundleGetBundleWithIdentifier(CFSTR("com.apple.opengl"));
  if(openglFramework == NULL) {
    fatalError(@"Could not load Apple OpenGL.");
  }

  signal(SIGINT, handleSigint);

  [GameApplication sharedApplication];
  [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

  setupMenu();

  [NSApp finishLaunching];

  appDelegate = [[GameAppDelegate alloc] init];
  [NSApp setDelegate:appDelegate];

  createWindow();
  createContext();
  [context makeCurrentContext];
  [context setView:view];
}

int main() {
  initialize();

  while(shouldTerminate == NO) {
    pollEvents();
  }

  terminate();
  return 0;
}
