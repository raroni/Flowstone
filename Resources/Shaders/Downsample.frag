#version 330

in vec2 texCoords;

uniform sampler2D depthTexture;
uniform sampler2D normalTexture;

uniform float factor = 2.0; // todo: flyt ud i uniform
uniform float zNear = 4.5;
uniform float zFar = 10.0;

layout (location = 0) out float resultDepth;
layout (location = 1) out vec3 resultNormal;

const ivec2 offsets[4] = ivec2[](
  ivec2(-0.25, 0.25),
  ivec2(0.25, 0.25),
  ivec2(0.25, -0.25),
  ivec2(-0.25, -0.25)
);

vec3 fetchNormal(int offsetIndex) {
  ivec2 offset = offsets[offsetIndex];
  ivec2 texel = ivec2(ivec2((gl_FragCoord.xy+offset)*factor));
  return texelFetch(normalTexture, texel, 0).xyz;
}

float calcLinearDepth(int offsetIndex) {
  ivec2 offset = offsets[offsetIndex];
  float bufferDepth = texelFetch(depthTexture, ivec2((gl_FragCoord.xy+offset)*factor), 0).r;
  float normalizedDepth = bufferDepth*2.0-1.0;
  float linearDepth = 2.0 * zNear * zFar / (zFar + zNear - normalizedDepth * (zFar - zNear));
  return linearDepth;
}

float calcBufferDepth(float linearDepth) {
  float normalizedDepth = (zFar+zNear-((2*zNear*zFar)/linearDepth))/(zFar-zNear);
  return normalizedDepth*0.5+0.5;
}

ivec2 findMedians(int minDepthIndex, int maxDepthIndex) {
  ivec2 medians = ivec2(0, 0);
  int medianIndex = 0;
  for(int i=0; i<4 && medianIndex<2; ++i) {
    if(i != maxDepthIndex && i != minDepthIndex) {
      medians[medianIndex++] = i;
    }
  }
  return medians;
}

void main() {
  float depths[4];
  depths[0] = calcLinearDepth(0);
  depths[1] = calcLinearDepth(1);
  depths[2] = calcLinearDepth(2);
  depths[3] = calcLinearDepth(3);

  float minDepth = depths[0];
  int minDepthIndex = 0;
  float maxDepth = depths[0];
  int maxDepthIndex = 0;
  for(int i=1; i<4; ++i) {
    if(depths[i] < minDepth) {
      minDepth = depths[i];
      minDepthIndex = i;
    }
    else if(depths[i] > maxDepth) {
      maxDepth = depths[i];
      maxDepthIndex = i;
    }
  }

  ivec2 medianIndices = findMedians(minDepthIndex, maxDepthIndex);

  if(maxDepth-minDepth < 0.1) {
    float depth = (depths[medianIndices.x]+depths[medianIndices.y])*0.5;
    resultDepth = calcBufferDepth(depth);
    resultNormal = (fetchNormal(medianIndices.x)+fetchNormal(medianIndices.y))*0.5;
  } else {
    resultDepth = calcBufferDepth(depths[medianIndices.x]);
    resultNormal = fetchNormal(medianIndices.x);
  }
}
