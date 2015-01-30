#version 330

flat in vec4 passedAppearance;
flat in vec3 passedNormal;

layout (location = 0) out vec4 fragAppearance;
layout (location = 1) out vec3 fragNormal;

void main() {
  fragAppearance = passedAppearance;
  fragNormal = passedNormal;
}
