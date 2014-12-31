#version 330

out vec3 fragColor;
in vec2 texCoords;

uniform sampler2D diffuse;
uniform sampler2D normal;
uniform sampler2D depth;
uniform sampler2D shadow;

uniform mat4 cameraClipWorldTransform;
uniform mat4 lightWorldClipTransform;
uniform vec3 inversePrimaryLightDirection;
uniform vec3 primaryLightColor;
uniform vec3 inverseSecondaryLightDirection;

void main() {
  float depth = texture(depth, texCoords).r;
  vec3 fragmentNDCPosition = vec3(texCoords, depth)*2-1;
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

  vec3 atmosphereInfluence = primaryLightColor * (0.5 + primaryLuminosity*0.4 + secondaryLuminosity*0.1);

  fragColor = texture(diffuse, texCoords).rgb * atmosphereInfluence;
}
