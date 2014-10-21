#include <sys/time.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AppKit/AppKit.h>
#include "Bro/OSX/Application.h"
#include "Bro/OSX/AppDelegate.h"
#include "Bro/Bro.h"

struct Bro {
  id appDelegate;
  id autoreleasePool;
  BroWindow *window;
  id view;
  id windowDelegate;
  BroEventCallback eventCallback;
  bool shouldTerminate;
  NSOpenGLContext *context;
};

static struct Bro bro;

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

static void createContext() {
  NSOpenGLPixelFormatAttribute attributes[] = {
    NSOpenGLPFADoubleBuffer,
    0
  };
  NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
  if(pixelFormat == nil) {
    NSLog(@"Could not create pixel format.");
    exit(1);
  }

  bro.context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];

  GLint sync = 1;
  [bro.context setValues:&sync forParameter:NSOpenGLCPSwapInterval];

  [pixelFormat release];
}

static void createWindow() {
  unsigned int styleMask = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask;

  bro.window = [[BroWindow alloc] initWithContentRect:NSMakeRect(0, 0, 800, 600)
                                                 styleMask:styleMask
                                                   backing:NSBackingStoreBuffered
                                                     defer:NO];
  if(bro.window == nil) {
    NSLog(@"Could not create window.");
    exit(1);
  }

  bro.window.title = [NSString stringWithUTF8String:"Hi"];
  bro.windowDelegate = [[BroWindowDelegate alloc] init];
  bro.window.delegate = bro.windowDelegate;

  // check whether you actually NEED to send bounds (maybe just send window, see glfw)
  NSView *contentView = bro.window.contentView;
  bro.view = [[BroView alloc] initWithFrame:contentView.bounds];
  bro.window.contentView = bro.view;

  [bro.window center];
  [bro.window makeKeyAndOrderFront:nil];
}

void broInitialize() {
  bro.shouldTerminate = false;
  bro.autoreleasePool = [[NSAutoreleasePool alloc] init];

  CFBundleRef openglFramework = CFBundleGetBundleWithIdentifier(CFSTR("com.apple.opengl"));
  if(openglFramework == NULL) {
    printf("Could not load Apple OpenGL.\n");
    exit(1);
  }

  [BroApplication sharedApplication];
  [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

  setupMenu();

  [NSApp finishLaunching];

  bro.appDelegate = [[BroAppDelegate alloc] init];
  [NSApp setDelegate:bro.appDelegate];

  createWindow();
  createContext();
  [bro.context makeCurrentContext];
  [bro.context setView:bro.view];
}

void broPollEvents() {
  while(true) {
      NSEvent *event = [NSApp nextEventMatchingMask:NSAnyEventMask
                                          untilDate:[NSDate distantPast]
                                             inMode:NSDefaultRunLoopMode
                                            dequeue:YES];
    if (event == nil) return;
    [NSApp sendEvent:event];
  }
}

bool broShouldTerminate() {
  return bro.shouldTerminate;
}

void broSetEventCallback(BroEventCallback callback) {
  bro.eventCallback = callback;
}

void broTerminate() {
  [bro.context release];

  bro.window.contentView = nil;
  [bro.view release];

  [bro.windowDelegate release];
  bro.window.delegate = nil;

  [bro.window release];

  [NSApp setDelegate:nil];
  [bro.appDelegate release];

  [bro.autoreleasePool release];
}

void broSwapBuffers() {
  [bro.context flushBuffer];
}

void broRequestTermination() {
  bro.shouldTerminate = true;
}

bool broIsVisible() {
  return bro.window.isVisible;
}

uint64_t broGetTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec*1000000+tv.tv_usec);
}
