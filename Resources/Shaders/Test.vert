#version 330

in vec3 position;

uniform mat4 viewClipTransformation;
uniform mat4 worldViewTransformation;
uniform mat4 modelWorldTransformation;

void main() {
  gl_Position = viewClipTransformation*worldViewTransformation*modelWorldTransformation*vec4(position, 1);
}
