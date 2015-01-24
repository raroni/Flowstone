#version 330

noperspective in vec2 texCoords;

out vec2 result;

uniform vec2 offset;
uniform sampler2D sourceTexture;

void main() {
  result = vec2(0.0);
  result += texture(sourceTexture, texCoords+vec2(-3.0*offset.x, -3.0*offset.y)).xy*0.015625;
  result += texture(sourceTexture, texCoords+vec2(-2.0*offset.x, -2.0*offset.y)).xy*0.09375;
  result += texture(sourceTexture, texCoords+vec2(-1.0*offset.x, -1.0*offset.y)).xy*0.234375;
  result += texture(sourceTexture, texCoords+vec2(0.0, 0.0)).xy*0.3125;
  result += texture(sourceTexture, texCoords+vec2(1.0*offset.x, 1.0*offset.y)).xy*0.234375;
  result += texture(sourceTexture, texCoords+vec2(2.0*offset.x, 2.0*offset.y)).xy*0.09375;
  result += texture(sourceTexture, texCoords+vec2(3.0*offset.x, 3.0*offset.y)).xy*0.015625;
}
