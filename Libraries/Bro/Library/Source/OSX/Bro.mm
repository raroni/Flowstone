#include <sys/time.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AppKit/AppKit.h>
#include <stdlib.h>
#include "Bro/OSX/Application.h"
#include "Bro/OSX/AppDelegate.h"
#include "Bro/Bro.h"

void defaultKeyCallback(BroKey key) { }

struct Bro {
  id appDelegate;
  id autoreleasePool;
  BroWindow *window;
  id view;
  id windowDelegate;
  BroEventCallback eventCallback;
  BroKeyCallback keyDownCallback = defaultKeyCallback;
  BroKeyCallback keyUpCallback = defaultKeyCallback;
  bool shouldTerminate;
  NSOpenGLContext *context;
  uint64_t startTime;
  bool keyPresses[128];
};

static struct Bro bro;

static void handleSigint(int signum) {
  broRequestTermination();
}

static void fatalError(const char *message) {
  printf("Bro error:\n%s\n", message);
  exit(1);
}

static uint64_t getSystemTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec*1000000+tv.tv_usec);
}

double broGetTime() {
  uint64_t elapsed = getSystemTime()-bro.startTime;
  return elapsed*0.000001;
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

static void createContext() {
  NSOpenGLPixelFormatAttribute attributes[] = {
    NSOpenGLPFADoubleBuffer,
    NSOpenGLPFAOpenGLProfile,
    NSOpenGLProfileVersion3_2Core,
    0
  };
  NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
  if(pixelFormat == nil) {
    fatalError("Could not create pixel format.");
  }

  bro.context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];

  GLint sync = 1;
  [bro.context setValues:&sync forParameter:NSOpenGLCPSwapInterval];

  [pixelFormat release];
}

static void createWindow(BroResolution resolution) {
  unsigned int styleMask = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask;

  bro.window = [[BroWindow alloc] initWithContentRect:NSMakeRect(0, 0, resolution.width, resolution.height)
                                                 styleMask:styleMask
                                                   backing:NSBackingStoreBuffered
                                                     defer:NO];
  if(bro.window == nil) {
    fatalError("Could not create window.");
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

void broInitialize(BroResolution resolution) {
  bro.shouldTerminate = false;
  bro.autoreleasePool = [[NSAutoreleasePool alloc] init];

  bro.startTime = getSystemTime();

  CFBundleRef openglFramework = CFBundleGetBundleWithIdentifier(CFSTR("com.apple.opengl"));
  if(openglFramework == NULL) {
    fatalError("Could not load Apple OpenGL.");
  }

  signal(SIGINT, handleSigint);

  [BroApplication sharedApplication];
  [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

  setupMenu();

  [NSApp finishLaunching];

  bro.appDelegate = [[BroAppDelegate alloc] init];
  [NSApp setDelegate:bro.appDelegate];

  createWindow(resolution);
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

void broSetKeyDownCallback(BroKeyCallback callback) {
  bro.keyDownCallback = callback;
}

void broSetKeyUpCallback(BroKeyCallback callback) {
  bro.keyUpCallback = callback;
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

void broHandleKeyDown(BroKey key) {
  bro.keyPresses[key] = true;
  bro.keyDownCallback(key);
}

void broHandleKeyUp(BroKey key) {
  bro.keyPresses[key] = false;
  bro.keyUpCallback(key);
}

void broSwapBuffers() {
  [bro.context flushBuffer];
}

bool broIsKeyPressed(BroKey key) {
  return bro.keyPresses[key];
}

void broRequestTermination() {
  bro.shouldTerminate = true;
}

bool broIsVisible() {
  return bro.window.isVisible;
}

BroResolution broGetResolution() {
  struct BroResolution resolution;
  CGSize size = [bro.window.contentView frame].size;
  resolution.width = size.width;
  resolution.height = size.height;
  return resolution;
}
