#version 330

in vec3 interpolatedColor;
in float interpolatedLambert;
in vec3 interpolatedNormal;

layout (location = 0) out vec3 fragColor;
layout (location = 1) out float fragLambert;
layout (location = 2) out vec3 fragNormal;

void main() {
  fragColor = interpolatedColor;
  fragLambert = interpolatedLambert;
  fragNormal = interpolatedNormal;
}
