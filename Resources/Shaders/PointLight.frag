#version 330

flat in vec3 center;
flat in float radius;

out vec3 result;

uniform sampler2D depthTexture;
uniform sampler2D normalTexture;
uniform mat4 cameraClipWorldTransform;
uniform vec2 resolution;

void main() {
  ivec2 texelCoord = ivec2(gl_FragCoord.xy-0.5);
  float bufferDepth = texelFetch(depthTexture, texelCoord, 0).r;
  vec3 normalizedTexelCoords = vec3(gl_FragCoord.xy/resolution, bufferDepth);
  vec3 fragmentNDCPosition = vec3(normalizedTexelCoords)*2-1;
  vec4 a = cameraClipWorldTransform * vec4(fragmentNDCPosition, 1.0);
  vec3 fragmentWorldPosition = a.xyz/a.w;

  vec3 difference = fragmentWorldPosition-center;
  float distance = length(difference);

  vec3 worldNormal = texelFetch(normalTexture, texelCoord, 0).xyz;
  float lambert = max(0, dot(normalize(difference), -worldNormal));
  float progress = distance/radius;
  float cutoff = 1-pow(progress, 8);
  float attenuation = (1/(1 + progress*2 + pow(progress, 2)*4)) * cutoff;
  result = vec3(1.0, 0.63, 0.05) * attenuation * lambert;
}
