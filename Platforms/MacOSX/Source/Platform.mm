#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include "MacOSX/SysKey.h"
#include "MacOSX/GameApplication.h"
#include "MacOSX/GameAppDelegate.h"
#include "MacOSX/GameWindow.h"
#include "MacOSX/GameWindowDelegate.h"
#include "UserGame.h"
#include "Platform.h"

NSAutoreleasePool *autoreleasePool;
static id appDelegate;
static GameWindow *window;
static id windowDelegate;
static NSOpenGLContext *context;

static void fatalError(NSString *message) {
  NSLog(@"Mac OSX system error: %@\n", message);
  exit(1);
}

static void handleSigint(int signum) {
  UserGame::requestTermination();
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

static void createWindow(uint16_t resolutionWidth, uint16_t resolutionHeight) {
  unsigned int styleMask = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask;

  window = [[GameWindow alloc] initWithContentRect:NSMakeRect(0, 0, resolutionWidth, resolutionHeight)
                                                 styleMask:styleMask
                                                   backing:NSBackingStoreBuffered
                                                     defer:NO];
  if(window == nil) {
    fatalError(@"Could not create window.");
  }

  window.title = [NSString stringWithUTF8String:"Hi"];
  windowDelegate = [[GameWindowDelegate alloc] init];
  window.delegate = windowDelegate;

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

    switch(event.type) {
      case NSKeyDown:
      case NSKeyUp: {
        if(event.modifierFlags & NSCommandKeyMask) {
          [NSApp sendEvent:event];
        } else {
          SysKey::handleNSEvent(event);
        }
        break;
      }
      default:
        [NSApp sendEvent:event];
        break;
    }
  }
}

namespace Platform {
  void initialize(uint16_t resolutionWidth, uint16_t resolutionHeight) {
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

    createWindow(resolutionWidth, resolutionHeight);
    createContext();
    [context makeCurrentContext];
    [context setView:window.contentView];
  }

  void handlePreFrame() {
    pollEvents();
  }

  void handlePostFrame() {
    SysKey::clear();
  }

  void present() {
    [context flushBuffer];
  }

  void terminate() {
    [context release];

    [windowDelegate release];
    window.delegate = nil;

    [window release];

    [NSApp setDelegate:nil];
    [appDelegate release];

    [autoreleasePool release];
  }
}
