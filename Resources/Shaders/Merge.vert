#version 330

layout (location = 0) in vec2 position;

noperspective out vec2 texCoords;

void main() {
  texCoords = position*0.5+0.5;
  gl_Position = vec4(position, 0, 1);
}
