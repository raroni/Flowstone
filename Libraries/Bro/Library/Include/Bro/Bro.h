#ifndef BRO_H
#define BRO_H

#include <stdint.h>
#include "Key.h"

typedef void (*BroEventCallback)();
typedef void (*BroKeyCallback)(BroKey broKey);

struct BroResolution {
  uint16_t width;
  uint16_t height;
};

void broInitialize();
void broSetEventCallback(BroEventCallback callback);
void broSetKeyDownCallback(BroKeyCallback callback);
void broSetKeyUpCallback(BroKeyCallback callback);
bool broShouldTerminate();
void broPollEvents();
void broTerminate();
void broRequestTermination();
void broSwapBuffers();
bool broIsVisible();
double broGetTime();
BroResolution broGetResolution();
void broHandleKeyDown(BroKey key);
void broHandleKeyUp(BroKey key);
bool broIsKeyPressed(BroKey key);

#endif
