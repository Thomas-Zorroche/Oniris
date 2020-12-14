#version 330 core

layout(location = 0) in vec3 aVertexPosition;

out vec3 TexCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;
uniform float lolV;

void main()
{
    TexCoords = aVertexPosition;
    vec4 pos = uMVPMatrix * vec4(aVertexPosition, 1.0);
    gl_Position = pos.xyww;
}  