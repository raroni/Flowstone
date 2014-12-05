#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

layout(std140) uniform global {
  mat4 viewClipTransformation;
  mat4 worldViewTransformation;
  vec3 inverseLightDirection;
};

out vec3 interpolatedColor;
out float interpolatedLambert;

uniform mat4 modelWorldTransform;

void main() {
  gl_Position = viewClipTransformation*worldViewTransformation*modelWorldTransform*vec4(position, 1);
  interpolatedLambert = dot(inverseLightDirection, normal)*0.4+0.6;
  interpolatedColor = color;
}
