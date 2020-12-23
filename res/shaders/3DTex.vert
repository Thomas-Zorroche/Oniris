#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexcoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;
uniform mat4 uModelMatrix;

out vec3 vPosition_vs;
out vec3 vNormals_vs;
out vec2 vVertexTexcoords;
out vec3 vWorldPosition;

uniform float u_fogDensity;
uniform float u_fogGradient;
uniform float u_fogHeight;

void main() {
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    vWorldPosition = vec3(uModelMatrix * vertexPosition);

    vPosition_vs = vec3(uMVMatrix * vertexPosition);
    vNormals_vs = vec3(uNormalMatrix * vertexNormal);
    vVertexTexcoords = aVertexTexcoords;

    gl_Position = uMVPMatrix * vertexPosition;
}