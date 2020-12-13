#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexcoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs;
out vec3 vNormals_vs;
out vec2 vVertexTexcoords;

out float vVisibility;

const float density = 0.0035;
const float gradient = 2.0;

void main() {
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    vPosition_vs = vec3(uMVMatrix * vertexPosition);
    vNormals_vs = vec3(uNormalMatrix * vertexNormal);
    vVertexTexcoords = aVertexTexcoords;

    gl_Position = uMVPMatrix * vertexPosition;

    float distance = length(gl_Position.xyz);
    vVisibility = exp(-pow((distance * density), gradient));
    vVisibility = clamp(vVisibility, 0.0, 1.0);
}