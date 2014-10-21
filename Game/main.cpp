#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <OpenGL/gl.h>
#include <stdlib.h>
#include "Bro/Bro.h"

static float x = 0;
static uint64_t lastTime;

int max(int a, int b) {
  if(a < b) {
    return b;
  } else {
    return a;
  }
}

static uint64_t getTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec*1000000+tv.tv_usec);
}

void update() {
  uint64_t newTime = getTime();
  float delta = (newTime-lastTime)*0.001;
  lastTime = newTime;
  if(delta > 50) return;

  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  x += 0.0001*delta;
  glColor3f(1, .85, .35);
  glBegin(GL_TRIANGLES);
  {
    glVertex3f(x+ 0, 0.6, 0);
    glVertex3f(x+ -0.2, -0.3, 0);
    glVertex3f(x+.2, -.3, 0);
  }
  glEnd();
}

uint64_t targetFrameRate = (1.0/60.0)*1000000;

void handleSigint(int signum) {
  broRequestTermination();
}

int main() {
  signal(SIGINT, handleSigint);
  //broSetEventCallback(handleEvent);
  broInitialize();
  lastTime = getTime();
  while(!broShouldTerminate()) {
    broPollEvents();
    uint64_t start = getTime();
    update();
    broSwapBuffers();
    uint64_t duration = getTime()-start;
    int budgetRest = (int)(targetFrameRate-duration);
    usleep(max(budgetRest, 0));
  }
  broTerminate();
}
