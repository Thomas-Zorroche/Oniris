#version 330 core

out vec4 fFragColor;

in vec3 vNormals_vs;
in vec3 vPosition_vs;
in vec2 vVertexTexcoords;
in vec3 vWorldPosition;

uniform vec3 u_SkyColor;
uniform float u_lowerLimitFog;
uniform float u_upperLimitFog;
uniform vec3 u_LightDir_vs;

uniform sampler2D maskTexture;

vec3 Fog( in vec3  pixelColor,      // original color of the pixel
          in float distance,        // camera to point distance
          in vec3  rayDir,          // camera to point vector
          in vec3  sunDir )         // sun light direction
{
    float be = 0.01f;
    float bi = 0.01f;

    float sunAmount = max( dot( rayDir, sunDir ), 0.0 );
    vec3  fogColor  = mix( vec3(0.5,0.6,0.7), // bluish
                           vec3(1.0,0.9,0.7), // yellowish
                           pow(sunAmount * 0.01, 1.0) );
    
    return fogColor * (1.0 - exp(-distance * be)) + pixelColor * exp(-distance * bi);
}

void main()
{
    vec4 mask = texture(maskTexture, vVertexTexcoords);

    float factorFog = (vWorldPosition.y - u_lowerLimitFog) / (u_upperLimitFog - u_lowerLimitFog);
    factorFog = clamp(factorFog, 0.0, 1.0);

    // Grass Constant Color
    vec3 grassColor = vec3(0.1f, 0.4f, 0.3f);

    fFragColor = vec4( mix(Fog(grassColor.rgb, length(vPosition_vs.xyz), vPosition_vs, u_LightDir_vs), fFragColor.rgb, factorFog) , 1.0);
    fFragColor = mix(vec4(0.0f, 0.0f, 0.0f, 0.0f), fFragColor, mask.r);
}
