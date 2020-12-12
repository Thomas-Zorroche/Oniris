#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexcoords;

uniform mat4 uModelMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;


out vec3 vPosition_vs;
out vec3 vNormals_vs;
out vec2 vVertexTexcoords;

mat4 translation3D(float x)
{
    return mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(x, 0, 0, 1));
}


void main() {
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    vPosition_vs = vec3(uMVMatrix * vertexPosition);
    vNormals_vs = vec3(uNormalMatrix * vertexNormal);
    vVertexTexcoords = aVertexTexcoords;

    gl_Position = uModelMatrix * vertexPosition;

}