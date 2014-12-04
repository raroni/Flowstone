#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(std140) uniform global {
  mat4 viewClipTransformation;
  mat4 worldViewTransformation;
};

out vec3 interpolatedColor;
out float interpolatedLambert;

void main() {
  gl_Position = viewClipTransformation*worldViewTransformation*vec4(position, 1);

  vec3 worldLightDirection = normalize(vec3(-1, -3, 1)*-1);
  interpolatedLambert = dot(worldLightDirection, normal)*0.4+0.6;

  interpolatedColor = vec3(1, 0, 0);
}
