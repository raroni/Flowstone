#version 330

out float result;
noperspective in vec2 texCoords;

uniform sampler2D grainTexture;
uniform sampler2D depthTexture;

uniform vec2 grainTexelSize;
uniform float depthDifferenceLimit;

uniform float zNear;
uniform float zFar;

const int blurSize = 4;

float calcLinearDepth(in vec2 texelCoords) {
  float bufferDepth = texture(depthTexture, texelCoords).r;
  float normalizedDepth = bufferDepth*2.0-1.0;
  float linearDepth = 2.0 * zNear * zFar / (zFar + zNear - normalizedDepth * (zFar - zNear));
  return linearDepth;
}

void main() {
  float occlusion = 0;
  vec2 hlim = vec2(float(-blurSize) * 0.5 + 0.5);
  int sampleCount = 0;
  float mainDepth = calcLinearDepth(texCoords);
  for(int x=0; x<blurSize; ++x) {
    for(int y=0; y<blurSize; ++y) {
      vec2 offset = (hlim + vec2(float(x), float(y))) * grainTexelSize;
      vec2 sampleCoords = texCoords+offset;
      float sampleDepth = calcLinearDepth(texCoords+offset);
      float x = texture(grainTexture, sampleCoords).r;
      if(abs(sampleDepth-mainDepth) < depthDifferenceLimit) {
        sampleCount++;
        occlusion += x;
      }
    }
  }
  if(sampleCount == 0) {
    result = 1;
  } else {
    result = occlusion / sampleCount;
  }
}
