#include <math.h>
#include "AtmosphereColor.h"

struct Step {
  float progress;
  Quanta::Vector3 color;
};

AtmosphereColor::AtmosphereColor() {
  Quanta::Vector3 darkBlue(0.1, 0.1, 0.7);
  Quanta::Vector3 lightBlue(0.2, 0.2, 1);
  Quanta::Vector3 orange(1, 0.24, 0.24);
  Quanta::Vector3 white(1, 1, 1);

  Step steps[] = {
    { 0, lightBlue },
    { 0.2, darkBlue },
    { 0.3, orange },
    { 0.4, white },
    { 0.6, white },
    { 0.7, orange },
    { 0.8, darkBlue },
    { 1, lightBlue },
  };

  uint8_t stepIndex = 0;
  for(uint16_t i=0; count>i; i++) {
    float progress = static_cast<float>(i)/count;
    if(progress >= steps[stepIndex+1].progress) {
      stepIndex++;
    }
    Step &previousStep = steps[stepIndex];
    Step &nextStep = steps[stepIndex+1];
    float stepProgress = (progress-previousStep.progress)/(nextStep.progress-previousStep.progress);
    Quanta::Vector3 &color = colors[i];
    for(uint8_t i=0; 3>i; i++) {
      color[i] = previousStep.color[i]*(1-stepProgress);
      color[i] += nextStep.color[i]*stepProgress;
    }
  }
}

const Quanta::Vector3& AtmosphereColor::get(float progress) {
  uint16_t index = floor(progress*count);
  return colors[index];
}
