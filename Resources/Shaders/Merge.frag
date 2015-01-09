#version 330

out vec3 fragColor;
in vec2 texCoords;

uniform sampler2D diffuse;
uniform sampler2D normal;
uniform sampler2D depth;
uniform sampler2D shadow;
uniform sampler2D lowResDepthTexture;
uniform sampler2D ssaoTexture;

uniform mat4 cameraClipWorldTransform;
uniform mat4 lightWorldClipTransform;
uniform vec3 inversePrimaryLightDirection;
uniform vec3 primaryLightColor;
uniform vec3 inverseSecondaryLightDirection;

uniform float zNear;
uniform float zFar;

float calcLinearDepth(float bufferDepth) {
  float normalizedDepth = bufferDepth*2.0-1.0;
  return 2.0 * zNear * zFar / (zFar + zNear - normalizedDepth * (zFar - zNear));
}

float calcOcclusion() {
  float mainDepth = calcLinearDepth(texture(depth, texCoords).x);

  float ao = 0.0;
  float weight = 0.0;

  vec2 lowResCoords[4];
  lowResCoords[0] = floor((gl_FragCoord.xy + vec2(-1.0, 1.0)) / 2.0); // todo: 2.0 skal trækkes ud i en uniform
  lowResCoords[1] = floor((gl_FragCoord.xy + vec2(1.0, 1.0)) / 2.0);
  lowResCoords[2] = floor((gl_FragCoord.xy + vec2(-1.0, -1.0)) / 2.0);
  lowResCoords[3] = floor((gl_FragCoord.xy + vec2(1.0, -1.0)) / 2.0);

  for(int i=0; i<4; i++) {
    float sampleDepth = calcLinearDepth(texelFetch(lowResDepthTexture, ivec2(lowResCoords[i]), 0).x);
    float sampleAO = texelFetch(ssaoTexture, ivec2(lowResCoords[i]), 0).x;
    float sampleWeight = 1.0/(1.0 + abs(sampleDepth-mainDepth));
    sampleWeight = pow(sampleWeight, 32);
    weight += sampleWeight;
    ao += sampleAO*sampleWeight;
  }
  return ao/weight;
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

  vec3 atmosphereInfluence = primaryLightColor * (0.5 + 0.4*primaryLuminosity + 0.1*secondaryLuminosity);
  fragColor = texture(diffuse, texCoords).rgb * atmosphereInfluence * (0.2 + calcOcclusion()*0.8);
}
