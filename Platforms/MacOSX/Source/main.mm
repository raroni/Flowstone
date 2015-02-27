#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import "MacOSX/Timing.h"
#import "MacOSX/Util.h"
#import "MacOSX/GameView.h"
#import "MacOSX/GameApplication.h"
#import "MacOSX/GameAppDelegate.h"
#import "MacOSX/GameWindow.h"
#import "MacOSX/GameWindowDelegate.h"
#include "Rendering/Renderer.h"

NSAutoreleasePool *autoreleasePool;
static id appDelegate;
static GameWindow *window;
static GameView *view;
static id windowDelegate;
static NSOpenGLContext *context;

static Rendering::Renderer renderer;
static struct {
  const uint16_t width = 800;
  const uint16_t height = 600;
} resolution;

static void fatalError(NSString *message) {
  NSLog(@"Mac OSX system error: %@\n", message);
  exit(1);
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

  [menu release];
  [quitItem release];
  [barItem release];
  [bar release];
}

static void createWindow() {
  unsigned int styleMask = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask;

  window = [[GameWindow alloc] initWithContentRect:NSMakeRect(0, 0, resolution.width, resolution.height)
                                                 styleMask:styleMask
                                                   backing:NSBackingStoreBuffered
                                                     defer:NO];
  if(window == nil) {
    fatalError(@"Could not create window.");
  }

  window.title = [NSString stringWithUTF8String:"Hi"];
  windowDelegate = [[GameWindowDelegate alloc] init];
  window.delegate = windowDelegate;

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

int main() {
  initialize();
  timingInitialize();
  renderer.initialize();
  renderer.updateResolution({ resolution.width, resolution.height });
  //flow.initialize(renderer);

  while(shouldTerminate == NO) {
    timingStartFrame();

    pollEvents();
    double timeDelta = timingGetDelta();
    NSLog(@"Time: %f\n", timeDelta);
    //flow.update(timeDelta);
    renderer.draw();
    //swapBuffers();
    timingWaitForNextFrame();
  }

  terminate();
  return 0;
}
