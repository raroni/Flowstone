#ifndef BRO_H
#define BRO_H

#include <stdint.h>

typedef void (* BroEventCallback)();

struct BroResolution {
  uint16_t width;
  uint16_t height;
};

void broInitialize();
void broSetEventCallback(BroEventCallback callback);
bool broShouldTerminate();
void broPollEvents();
void broTerminate();
void broRequestTermination();
void broSwapBuffers();
bool broIsVisible();
double broGetTime();
BroResolution broGetResolution();

#endif
