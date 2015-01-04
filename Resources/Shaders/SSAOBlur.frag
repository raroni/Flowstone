#version 330

out float result;
in vec2 texCoords;

uniform sampler2D grainTexture;
uniform sampler2D depthTexture;

uniform vec2 grainTexelSize;
uniform float depthDifferenceLimit;

const int blurSize = 4;

void main() {
  float occlusion = 0;
  vec2 hlim = vec2(float(-blurSize) * 0.5 + 0.5);
  int sampleCount = 0;
  float mainDepth = texture(depthTexture, texCoords).r;
  for(int x=0; x<blurSize; ++x) {
    for(int y=0; y<blurSize; ++y) {
      vec2 offset = (hlim + vec2(float(x), float(y))) * grainTexelSize;
      vec2 sampleCoords = texCoords+offset;
      float sampleDepth = texture(depthTexture, sampleCoords).r;
      float x = texture(grainTexture, sampleCoords).r;
      if(abs(sampleDepth-mainDepth) < depthDifferenceLimit) {
        sampleCount++;
        occlusion += x;
      }
    }
  }
  result = occlusion / sampleCount;
}
