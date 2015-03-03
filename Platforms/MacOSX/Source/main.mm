#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import "MacOSX/Timing.h"
#import "MacOSX/Util.h"
#import "MacOSX/GameApplication.h"
#import "MacOSX/GameAppDelegate.h"
#import "MacOSX/GameWindow.h"
#import "MacOSX/GameWindowDelegate.h"
#import "GameClient.h"
#import "KeyboardKey.h"

NSAutoreleasePool *autoreleasePool;
static id appDelegate;
static GameWindow *window;
static id windowDelegate;
static NSOpenGLContext *context;

GameClient gameClient;
GameClientInput gameClientInput;
GameClientOutput gameClientOutput;

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

static KeyboardKey convertKeyCode(unsigned short keyCode) {
  if(keyCode > 127) return KeyboardKey::Unknown;

  static const KeyboardKey table[] = {
    KeyboardKey::A,
    KeyboardKey::S,
    KeyboardKey::D,
    KeyboardKey::F,
    KeyboardKey::H,
    KeyboardKey::G,
    KeyboardKey::Z,
    KeyboardKey::X,
    KeyboardKey::C,
    KeyboardKey::V,
    KeyboardKey::Unknown,
    KeyboardKey::B,
    KeyboardKey::Q,
    KeyboardKey::W,
    KeyboardKey::E,
    KeyboardKey::R,
    KeyboardKey::Y,
    KeyboardKey::T,
    KeyboardKey::Num1,
    KeyboardKey::Num2,
    KeyboardKey::Num3,
    KeyboardKey::Num4,
    KeyboardKey::Num6,
    KeyboardKey::Num5,
    KeyboardKey::Unknown,
    KeyboardKey::Num9,
    KeyboardKey::Num7,
    KeyboardKey::Unknown,
    KeyboardKey::Num8,
    KeyboardKey::Num0,
    KeyboardKey::Unknown,
    KeyboardKey::O,
    KeyboardKey::U,
    KeyboardKey::Unknown,
    KeyboardKey::I,
    KeyboardKey::P,
    KeyboardKey::Enter,
    KeyboardKey::L,
    KeyboardKey::J,
    KeyboardKey::Unknown,
    KeyboardKey::K,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Comma,
    KeyboardKey::Unknown,
    KeyboardKey::N,
    KeyboardKey::M,
    KeyboardKey::Period,
    KeyboardKey::Tab,
    KeyboardKey::Space,
    KeyboardKey::Unknown,
    KeyboardKey::Backspace,
    KeyboardKey::Unknown,
    KeyboardKey::Escape,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Capslock,
    KeyboardKey::LeftAlt,
    KeyboardKey::LeftControl,
    KeyboardKey::RightShift,
    KeyboardKey::RightAlt,
    KeyboardKey::RightControl,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Unknown,
    KeyboardKey::Left,
    KeyboardKey::Right,
    KeyboardKey::Down,
    KeyboardKey::Up,
    KeyboardKey::Unknown
  };

  return table[keyCode];
}

static void pollEvents(KeyboardInput &keyboard) {
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
          KeyboardEvent gameEvent;
          gameEvent.key = convertKeyCode(event.keyCode);
          if(event.type == NSKeyDown) {
            gameEvent.type = KeyboardEventType::Down;
          } else {
            gameEvent.type = KeyboardEventType::Up;
          }
          keyboard.write(gameEvent);
        }
        break;
      }
      default:
        [NSApp sendEvent:event];
        break;
    }
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
  [context setView:window.contentView];
}

static void terminate() {
  [context release];

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
  gameClient.initialize(resolution.width, resolution.height);

  while(shouldTerminate == NO) {
    timingStartFrame();
    gameClientInput.clear();
    pollEvents(gameClientInput.keyboard);
    gameClientInput.timeDelta = timingGetDelta();
    gameClientOutput.clear();
    gameClient.update(gameClientInput, gameClientOutput);
    [context flushBuffer];
    timingWaitForNextFrame();
  }

  terminate();
  return 0;
}
