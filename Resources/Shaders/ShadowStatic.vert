#version 330

layout(location = 0) in vec3 position;

out float linearDepth;

uniform mat4 worldClipTransform;
uniform mat4 modelWorldTransform;

void main() {
  vec4 worldPosition = modelWorldTransform*vec4(position, 1);
  linearDepth = worldPosition.z;
  gl_Position = worldClipTransform*worldPosition;
}
