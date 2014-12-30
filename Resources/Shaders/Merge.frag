#version 330

out vec3 fragColor;
in vec2 texCoords;

uniform sampler2D diffuse;
uniform sampler2D normal;
uniform sampler2D depth;
uniform sampler2D shadow;

uniform mat4 geometryClipWorldTransform;
uniform mat4 lightWorldClipTransform;
uniform vec3 lightDirection;
uniform vec3 atmosphereColor;

void main() {
  float depth = texture(depth, texCoords).r;
  if(depth == 1.0) {
    fragColor = vec3(1, 1, 1); // TODO: presumably not needed in final version
    return;
  }

  vec3 fragmentNDCPosition = vec3(texCoords, depth)*2-1;
  vec4 a = geometryClipWorldTransform * vec4(fragmentNDCPosition, 1.0);
  vec4 fragmentWorldPosition = vec4(a.xyz/a.w, 1);
  vec4 lightClipPosition = lightWorldClipTransform * fragmentWorldPosition;
  vec3 lightNDCPosition = lightClipPosition.xyz/lightClipPosition.w;

  float luminosity;
  vec3 worldNormal = texture(normal, texCoords).xyz;
  if(dot(lightDirection, worldNormal) > -0.01) {
    luminosity = 0;
  }
  else if(lightNDCPosition.z*0.5+0.5 > texture(shadow, lightNDCPosition.xy*0.5+0.5).x) {
    luminosity = 0;
  } else {
    luminosity = dot(lightDirection*-1, worldNormal);
  }

  vec3 atmosphereInfluence = atmosphereColor * (0.5 + luminosity*0.5);

  fragColor = texture(diffuse, texCoords).rgb * atmosphereInfluence;
}
