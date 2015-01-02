#version 330

out vec3 fragColor;
in vec2 texCoords;

uniform sampler2D diffuse;
uniform sampler2D normal;
uniform sampler2D depth;
uniform sampler2D shadow;
uniform sampler2D ssao;

uniform mat4 cameraClipWorldTransform;
uniform mat4 lightWorldClipTransform;
uniform vec3 inversePrimaryLightDirection;
uniform vec3 primaryLightColor;
uniform vec3 inverseSecondaryLightDirection;

const int ssaoBlurSize = 4;

float blurSSAO(in vec2 texCoord) {
  float occlusion = 0;
  vec2 texelSize = 1.0/vec2(800, 600); // todo: precalc this
  vec2 hlim = vec2(float(-ssaoBlurSize) * 0.5 + 0.5);
  for(int x=0; x<ssaoBlurSize; ++x) {
    for(int y=0; y<ssaoBlurSize; ++y) {
      vec2 offset = (hlim + vec2(float(x), float(y))) * texelSize;
      occlusion += texture(ssao, texCoords + offset).r;
    }
  }
  occlusion = occlusion/float(ssaoBlurSize * ssaoBlurSize);
  return occlusion;
}

void main() {
  float aDepth = texture(depth, texCoords).r;
  vec3 fragmentNDCPosition = vec3(texCoords, aDepth)*2-1;
  vec4 a = cameraClipWorldTransform * vec4(fragmentNDCPosition, 1.0);
  vec4 fragmentWorldPosition = vec4(a.xyz/a.w, 1);
  vec4 lightClipPosition = lightWorldClipTransform * fragmentWorldPosition;
  vec3 lightNDCPosition = lightClipPosition.xyz/lightClipPosition.w;

  float primaryLuminosity;
  vec3 worldNormal = texture(normal, texCoords).xyz;
  if(dot(inversePrimaryLightDirection, worldNormal) < 0.01) {
    primaryLuminosity = 0;
  }
  else if(lightNDCPosition.z*0.5+0.5 > texture(shadow, lightNDCPosition.xy*0.5+0.5).x) {
    primaryLuminosity = 0;
  } else {
    primaryLuminosity = dot(inversePrimaryLightDirection, worldNormal);
  }

  float secondaryLuminosity = dot(inverseSecondaryLightDirection, worldNormal);

  float occlusion = blurSSAO(texCoords);

  vec3 atmosphereInfluence = primaryLightColor * (0.5 + 0.4*primaryLuminosity + 0.1*secondaryLuminosity);
  fragColor = texture(diffuse, texCoords).rgb * atmosphereInfluence * (0.2 + occlusion*0.8);
}
