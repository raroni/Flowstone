#version 330

layout(location = 0) in vec3 position;

uniform mat4 viewClipTransform;
uniform mat4 worldViewTransform;
uniform mat4 modelWorldTransform;

void main() {
  gl_Position = viewClipTransform*worldViewTransform*modelWorldTransform*vec4(position, 1);
}
