#version 330 core

out vec4 fFragColor;

in vec3 vNormals_vs;
in vec2 vVertexTexcoords;

uniform sampler2D uTexture;

void main()
{
    fFragColor = texture(uTexture, vVertexTexcoords);
}
