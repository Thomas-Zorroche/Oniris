#version 330 core

struct Material
{
    float shininess;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight 
{
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
}; 

struct DirLight 
{
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

out vec4 fFragColor;

in vec3 vNormals_vs;
in vec3 vPosition_vs;
in vec2 vVertexTexcoords;
in vec3 vFragPos;

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight;

uniform sampler2D u_Diffuse;

uniform vec3 u_SkyColor;
uniform float u_lowerLimitFog;
uniform float u_upperLimitFog;

vec3 Fog(in vec3 pixelColor, in float distance, in vec3 rayDir, in vec3  sunDir);
vec3 ComputeDirLight(Material material, DirLight dirLight, vec3 normal, vec3 viewDir);
vec3 ComputePointLight(Material material, DirLight dirLight, vec3 normal, vec3 vFragPos, vec3 viewDir);






void main()
{
    fFragColor = texture(u_Diffuse, vVertexTexcoords * 50.0) * vec4(BlinnPhong(), 1.0);
    fFragColor = mix(fFragColor, vec4(0.05, 0.14, 0.18, 1.0), 0.8);
    
    float factorFog = (vFragPos.y - u_lowerLimitFog) / (u_upperLimitFog - u_lowerLimitFog);
    factorFog = clamp(factorFog, 0.0, 1.0);

    fFragColor = vec4( mix(Fog(fFragColor.rgb, length(vPosition_vs.xyz), vPosition_vs, u_LightDir_vs), fFragColor.rgb, factorFog) , 1.0);

};


vec3 ComputeDirLight(Material material, DirLight dirLight, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-dirLight.direction);

    vec3 reflectDir = reflect(-lightDir, normal);

    float diffuseStrength = max(dot(normal, lightDir), 0.0);
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * material.diffuse * diffuseStrength;
    vec3 specular = light.specular * material.specular * specularStrength;

    return vec3(ambient + diffuse + specular);
}

vec3 ComputePointLight(Material material, DirLight dirLight, vec3 normal, vec3 vFragPos, vec3 viewDir)
{
    vec3 distance = normalize(-dirLight.direction - vFragPos);

    vec3 reflectDir = reflect(-lightDir, normal);

    float diffuseStrength = max(dot(normal, lightDir), 0.0);
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float attenuation = 1.0 / (1.0f + light.linear * distance + light.quadratic * (distance * distance));  

    vec3 ambient = light.ambient * material.ambient * attenuation;
    vec3 diffuse = light.diffuse * material.diffuse * diffuseStrength * attenuation;
    vec3 specular = light.specular * material.specular * specularStrength * attenuation;

    return vec3(ambient + diffuse + specular);
}

vec3 Fog( in vec3  pixelColor,      // original color of the pixel
          in float distance,        // camera to point distance
          in vec3  rayDir,          // camera to point vector
          in vec3  sunDir )         // sun light direction
{
    float be = 0.01f; // exctinction
    float bi = 0.04f; // inscattering

    float sunAmount = max( dot( rayDir, sunDir ), 0.0 );
    vec3  fogColor  = mix( vec3(0.5,0.6,0.7), // bluish
                           vec3(1.0,0.9,0.7), // yellowish
                           pow(sunAmount * 0.01, 1.0) );
    
    return fogColor * (1.0 - exp(-distance * be)) + pixelColor * exp(-distance * bi);
}