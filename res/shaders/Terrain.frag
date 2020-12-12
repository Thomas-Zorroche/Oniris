#version 330 core

out vec4 fFragColor;

in vec3 vNormals_vs;
in vec3 vPosition_vs;
in vec2 vVertexTexcoords;
in float vVisibility;


uniform sampler2D u_Diffuse;

uniform vec3 u_Kd;
uniform vec3 u_Ks;
uniform float u_Shininess;

uniform vec3 u_LightDir_vs;
uniform vec3 u_LightIntensity;

uniform vec3 u_SkyColor;

vec3 BlinnPhong()
{
    // Vecteur Pointant Vers la Camera
    vec3 viewDir = normalize(-vPosition_vs);
    vec3 Normal = normalize(vNormals_vs);
    vec3 LightDir = normalize(u_LightDir_vs);

    vec3 halfwayDir = (viewDir + LightDir) * 0.5;

    vec3 Color = u_LightIntensity * clamp((u_Kd * dot(LightDir, Normal) + u_Ks * pow(dot(halfwayDir, Normal), u_Shininess)), 0.2, 1);

    return Color;
}

void main()
{
    fFragColor = texture(u_Diffuse, vVertexTexcoords * 10.0) * vec4(BlinnPhong(), 1.0);
    fFragColor = mix(vec4(u_SkyColor, 1.0), fFragColor, vVisibility);
    //fFragColor = vec4(u_Kd, 1.0f);
};