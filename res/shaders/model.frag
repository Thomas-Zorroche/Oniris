#version 330 core

out vec4 fFragColor;

in vec3 vNormals_vs;
in vec3 vPosition_vs;
in vec2 vVertexTexcoords;

uniform sampler2D texture_diffuse1;

void main()
{
    fFragColor = texture(texture_diffuse1, vVertexTexcoords);
}
