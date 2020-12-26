#version 330 core

out vec4 fFragColor;

in vec3 vNormals_vs;
in vec3 vPosition_vs;
in vec2 vVertexTexcoords;
in vec3 vFragPos;

uniform sampler2D u_Diffuse;

uniform vec3 u_Kd;
uniform vec3 u_Ks;
uniform float u_Shininess;

uniform vec3 u_LightDir_vs;
uniform vec3 u_LightIntensity;
uniform vec3 u_SkyColor;
uniform float u_lowerLimitFog;
uniform float u_upperLimitFog;

vec3 BlinnPhong()
{
    // Vecteur Pointant Vers la Camera
    vec3 viewDir = normalize(-vPosition_vs);
    vec3 Normal = normalize(vNormals_vs);
    vec3 LightDir = normalize(u_LightDir_vs);

    vec3 halfwayDir = (viewDir + LightDir) * 0.5;

    vec3 Color = u_LightIntensity * clamp((u_Kd * dot(LightDir, Normal) + u_Ks * pow(dot(halfwayDir, Normal), u_Shininess)), 0.1, 1);

    return Color;
}

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

    fFragColor = texture(u_Diffuse, vVertexTexcoords) * vec4(BlinnPhong(), 1.0);

    float factorFog = (vWorldPosition.y - u_lowerLimitFog) / (u_upperLimitFog - u_lowerLimitFog);
    factorFog = clamp(factorFog, 0.0, 1.0);

    fFragColor = vec4( mix(Fog(fFragColor.rgb, length(vPosition_vs.xyz), vPosition_vs, u_LightDir_vs), fFragColor.rgb, factorFog) , 1.0);
}
