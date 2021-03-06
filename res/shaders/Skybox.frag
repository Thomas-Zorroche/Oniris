#version 330 core

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform vec3 u_skyColor;

const float lowerLimitFog = 0.0f;
const float upperLimitFog = 0.5f;

void main()
{    
    FragColor = texture(skybox, TexCoords);

    float factor = (TexCoords.y - lowerLimitFog) / (upperLimitFog - lowerLimitFog);
    factor = clamp(factor, 0.0, 1.0);

    FragColor = mix(vec4(u_skyColor, 1.0), FragColor, factor);
}
