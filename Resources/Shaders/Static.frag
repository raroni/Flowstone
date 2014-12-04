#version 330

in vec3 interpolatedColor;
in float interpolatedLambert;

layout (location = 0) out vec3 fragColor;
layout (location = 1) out float fragLambert;

void main() {
  fragColor = interpolatedColor;
  fragLambert = interpolatedLambert;
}
