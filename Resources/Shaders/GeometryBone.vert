#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 3) in uint jointIndex;

layout(std140) uniform global {
  mat4 viewClipTransform;
  mat4 worldViewTransform;
  vec3 inverseLightDirection;
};

out vec3 interpolatedColor;
out float interpolatedLambert;
out vec3 interpolatedNormal;

uniform mat4 jointWorldTransform;
uniform mat4 modelJointTransforms[8];

void main() {
  vec4 jointPosition = modelJointTransforms[jointIndex]*vec4(position, 1);
  gl_Position = viewClipTransform*worldViewTransform*jointWorldTransform*jointPosition;

  vec3 worldNormal = (jointWorldTransform*vec4(normal, 0)).xyz; // assuming no scaling
  interpolatedLambert = dot(inverseLightDirection, worldNormal);

  interpolatedColor = vec3(0.3, 0.6, 0.95);
  interpolatedNormal = worldNormal;
}