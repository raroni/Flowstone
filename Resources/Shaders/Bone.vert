#version 330

in vec3 position;
in uint jointIndex;

layout(std140) uniform global {
  mat4 viewClipTransformation;
  mat4 worldViewTransformation;
};

uniform mat4 jointWorldTransformation;
uniform mat4 modelJointTransformations[8];

void main() {
  vec4 jointPosition = modelJointTransformations[jointIndex]*vec4(position, 1);
  gl_Position = viewClipTransformation*worldViewTransformation*jointWorldTransformation*jointPosition;
}
