#version 330

layout(location = 0) in vec3 position;

uniform mat4 worldClipTransform;
uniform mat4 modelWorldTransform;

void main() {
  gl_Position = worldClipTransform*modelWorldTransform*vec4(position, 1);
}
