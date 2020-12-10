#version 330 core

out vec4 fFragColor;

in vec3 vNormals_vs;
in vec3 vPosition_vs;
in vec2 vVertexTexcoords;


void main()
{
    fFragColor = vec4(0.8, 0.4, 0.0, 1.0);
}
