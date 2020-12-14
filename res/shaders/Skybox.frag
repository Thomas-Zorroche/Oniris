#version 330 core

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform vec3 u_colorFog;

const float lowerLimitFog = 0.0f;
const float upperLimitFog = 1.0f;

void main()
{    
    FragColor = texture(skybox, TexCoords);

    float factor = (TexCoords.y - lowerLimitFog) / (upperLimitFog - lowerLimitFog);
    factor = clamp(factor, 0.0, 1.0);

    FragColor = mix(vec4(u_colorFog, 1.0), FragColor, factor);
}