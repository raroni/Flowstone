#version 330

noperspective in vec2 texCoords;

out vec2 result;

uniform vec2 offset;
uniform sampler2D sourceTexture;

float gaussFilter[7] = float[7](
  0.015625,
  0.09375,
  0.234375,
  0.3125,
  0.234375,
  0.09375,
  0.015625
);

void main() {
  result = vec2(0.0);
  for(int i=0; i<7; ++i) {
    vec2 sample = texture(sourceTexture, texCoords+offset*(i-3)).xy;
    result += sample*gaussFilter[i];
  }
}
