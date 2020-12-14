#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexcoords;

uniform mat4 uModelMatrix;
uniform vec2 uTexTranslation;
uniform mat4 uNormalMatrix;


out vec3 vPosition_vs;
out vec3 vNormals_vs;
out vec2 vVertexTexcoords;

void main() {
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    vNormals_vs = vec3(uNormalMatrix * vertexNormal);
    vVertexTexcoords = uTexTranslation + aVertexTexcoords;

    gl_Position = uModelMatrix * vertexPosition;

}