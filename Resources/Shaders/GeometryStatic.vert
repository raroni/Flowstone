#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

layout(std140) uniform global {
  mat4 viewClipTransform;
  mat4 worldViewTransform;
  vec3 inverseLightDirection;
};

out vec3 interpolatedColor;
out float interpolatedLambert;
out vec3 interpolatedNormal;

uniform mat4 modelWorldTransform;

void main() {
  gl_Position = viewClipTransform*worldViewTransform*modelWorldTransform*vec4(position, 1);

  vec3 worldNormal = (modelWorldTransform*vec4(normal, 0)).xyz; // assuming no scaling

  interpolatedLambert = dot(inverseLightDirection, worldNormal);
  interpolatedColor = color;
  interpolatedNormal = worldNormal;
}
