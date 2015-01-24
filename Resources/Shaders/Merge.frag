#version 330

out vec3 fragColor;
noperspective in vec2 texCoords;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;
uniform sampler2D depthTexture;
uniform sampler2D shadowTexture;
uniform sampler2D lowResDepthTexture;
uniform sampler2D ssaoTexture;

uniform mat4 cameraClipWorldTransform;
uniform mat4 lightWorldViewTransform;
uniform mat4 lightViewClipTransform;
uniform vec3 inversePrimaryLightDirection;
uniform vec3 primaryLightColor;
uniform vec3 inverseSecondaryLightDirection;

uniform float zNear;
uniform float zFar;
uniform uint downsampleScale;
uniform float inverseShadowSize;

const float shadowBias = 0.005;

float calcLinearDepth(float bufferDepth) {
  float normalizedDepth = bufferDepth*2.0-1.0;
  return 2.0 * zNear * zFar / (zFar + zNear - normalizedDepth * (zFar - zNear));
}

float calcShadow(vec2 shadowTextureCoords, float fragmentDepth) {
  vec2 depths = texture(shadowTexture, shadowTextureCoords).xy;
  float mean = depths.x;

  if(mean > fragmentDepth-shadowBias) {
    return 1;
  }

  float variance = depths.y-mean*mean;
  variance = max(variance, 0.00001);
  float meanDifference = fragmentDepth-depths.x;
  return variance/(variance + meanDifference*meanDifference);
}

float calcOcclusion() {
  float mainDepth = calcLinearDepth(texture(depthTexture, texCoords).x);

  float ao = 0.0;
  float weight = 0.0;

  vec2 lowResCoords[4];
  lowResCoords[0] = floor((gl_FragCoord.xy + vec2(-1.0, 1.0)) / downsampleScale);
  lowResCoords[1] = floor((gl_FragCoord.xy + vec2(1.0, 1.0)) / downsampleScale);
  lowResCoords[2] = floor((gl_FragCoord.xy + vec2(-1.0, -1.0)) / downsampleScale);
  lowResCoords[3] = floor((gl_FragCoord.xy + vec2(1.0, -1.0)) / downsampleScale);

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
  float primaryLuminosity;
  vec3 worldNormal = texture(normalTexture, texCoords).xyz;
  float lightDot = dot(inversePrimaryLightDirection, worldNormal);
  if(lightDot < 0.01) {
    primaryLuminosity = 0;
  } else {
    float bufferDepth = texture(depthTexture, texCoords).r;
    vec3 fragmentNDCPosition = vec3(texCoords, bufferDepth)*2-1;
    vec4 a = cameraClipWorldTransform * vec4(fragmentNDCPosition, 1.0);
    vec4 fragmentWorldPosition = vec4(a.xyz/a.w, 1);
    vec4 lightViewPosition = lightWorldViewTransform * fragmentWorldPosition;
    vec4 lightClipPosition = lightViewClipTransform * lightViewPosition;
    vec3 lightNDCPosition = lightClipPosition.xyz/lightClipPosition.w;
    vec3 shadowTextureCoords = lightNDCPosition*0.5+0.5;
    primaryLuminosity = lightDot*calcShadow(shadowTextureCoords.xy, lightViewPosition.z);
  }

  float secondaryLuminosity = dot(inverseSecondaryLightDirection, worldNormal);

  vec3 atmosphereInfluence = primaryLightColor * (0.5 + 0.4*primaryLuminosity + 0.1*secondaryLuminosity);
  fragColor = texture(diffuseTexture, texCoords).rgb * atmosphereInfluence * (0.2 + calcOcclusion()*0.8);
}
