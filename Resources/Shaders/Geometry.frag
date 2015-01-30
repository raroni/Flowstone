#version 330

flat in vec4 passedAppearance;
flat in vec3 passedNormal;

layout (location = 0) out vec4 appearance;
layout (location = 1) out vec3 normal;

void main() {
  appearance = passedAppearance;
  normal = passedNormal;
}
