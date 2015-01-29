#version 330

flat in vec3 passedColor;
flat in vec3 passedNormal;

layout (location = 0) out vec3 fragColor;
layout (location = 1) out vec3 fragNormal;

void main() {
  fragColor = passedColor;
  fragNormal = passedNormal;
}
