#version 330

flat out vec3 center;

layout(location = 0) in vec3 position;

layout(std140) uniform CameraTransforms {
  mat4 viewClipTransform;
  mat4 worldViewTransform;
};

uniform vec3 worldPosition;
uniform float radius;

void main() {
  vec4 vertexWorldPosition = vec4(position*radius+worldPosition, 1);
  gl_Position = viewClipTransform*worldViewTransform*vertexWorldPosition;
}
