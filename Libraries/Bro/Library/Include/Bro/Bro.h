#ifndef BRO_H
#define BRO_H

typedef void (* BroEventCallback)();

void broInitialize();
void broSetEventCallback(BroEventCallback callback);
bool broShouldTerminate();
void broPollEvents();
void broTerminate();
void broRequestTermination();
void broSwapBuffers();
bool broIsVisible();

#endif
