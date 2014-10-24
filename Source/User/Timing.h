#include <unistd.h>
#include "Bro/Bro.h"

void timingInitialize();
void timingStartFrame();
void timingWaitForNextFrame();
double timingGetDelta();
