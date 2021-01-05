#version 330 core

struct Material
{
    float shininess;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight 
{
    float intensity;
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct Fog 
{
    vec3 colorShadow;
    vec3 colorSun;
    float lowerLimitFog;
    float upperLimitFog;
}; 


out vec4 fFragColor;

in vec3 vNormal_vs;
in vec3 vFragPos_vs;
in vec2 vVertexTexcoords;
in vec3 vFragPos_os;
in vec3 vNormal_os;

uniform Material material;
uniform DirLight dirLight;
uniform Fog fog;

uniform vec3 cameraPos;

uniform sampler2D texture_diffuse;
uniform float uvScale;

vec3 ApplyFog(in vec3 pixelColor, in float distance, in vec3 rayDir, in vec3  sunDir);
vec3 ComputeDirLight(Material material, DirLight dirLight, vec3 normal, vec3 viewDir);


void main()
{
    // Normal and View direction in VIEW SPACE
    vec3 Normal_vs = normalize(vNormal_vs);
    vec3 viewDir_vs = normalize(-vFragPos_vs);
    
    float factorDeepFog = 1.0 / (1.0 + (length(vFragPos_vs) * 0.02));
    factorDeepFog = clamp(factorDeepFog, 0.0, 0.5);
    vec3 colorDeepFog = vec3(0.0, 0.1, 0.4);

    float factorFog = (vFragPos_os.y - fog.lowerLimitFog) / (fog.upperLimitFog - fog.lowerLimitFog);
    factorFog = clamp(factorFog, 0.0, 1.0);

    // Lighting
    vec3 finalColor = vec3(0.0f);
    finalColor += ComputeDirLight(material, dirLight, Normal_vs, viewDir_vs);

    // Texture
    fFragColor = texture(texture_diffuse, vVertexTexcoords * uvScale) * vec4(finalColor, 1.0f);

    // Simple Fog
    fFragColor = vec4( mix(ApplyFog(fFragColor.rgb, length(vFragPos_vs.xyz), vFragPos_vs, dirLight.direction), fFragColor.rgb, factorFog) , 1.0);
    
    // Deep Blue Fog
    fFragColor = mix(fFragColor, vec4(colorDeepFog, 1.0), factorDeepFog);
}


vec3 ComputeDirLight(Material material, DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.direction);

    vec3 reflectDir = reflect(-lightDir, normal);

    float diffuseStrength = max(dot(normal, lightDir), 0.0);
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.2), material.shininess);

    vec3 ambient = light.ambient * 0.1 * material.ambient;
    vec3 diffuse = light.diffuse * material.diffuse * diffuseStrength;
    vec3 specular = light.specular * material.specular * specularStrength;

    return vec3(ambient + diffuse + specular);
}


vec3 ApplyFog( in vec3  pixelColor,      // original color of the pixel
          in float distance,        // camera to point distance
          in vec3  rayDir,          // camera to point vector
          in vec3  sunDir )         // sun light direction
{
    float be = 0.01f; // exctinction
    float bi = 0.04f; // inscattering

    float sunAmount = max( dot( rayDir, sunDir ), 0.0 );
    vec3  fogColor  = mix( fog.colorShadow,
                           fog.colorSun,
                           pow(sunAmount * 0.005, 1.0) );
    
    return fogColor * (1.0 - exp(-distance * be)) + pixelColor * exp(-distance * bi);
}