#version 330

layout(location = 0) in vec3 position;

out vec4 viewPosition;

uniform mat4 worldViewTransform;
uniform mat4 viewClipTransform;
uniform mat4 modelWorldTransform;

void main() {
  viewPosition = worldViewTransform*modelWorldTransform*vec4(position, 1);
  gl_Position = viewClipTransform*viewPosition;
}
