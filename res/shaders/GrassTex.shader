#shader vertex
#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexcoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vVertexPosition_VS;
out vec3 vVertexNormal_VS;
out vec2 vVertexTexcoords;

void main() {
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    vVertexPosition_VS = vec3(uMVMatrix * vertexPosition);
    vVertexNormal_VS = vec3(uNormalMatrix * vertexNormal);
    vVertexTexcoords = aVertexTexcoords;

    gl_Position = uMVPMatrix * vertexPosition;
}


#shader fragment
#version 330 core

out vec4 fFragColor;

in vec3 vVertexNormal_VS;
in vec2 vVertexTexcoords;


uniform sampler2D Texture;

void main()
{
    fFragColor = texture(Texture, vVertexTexcoords * 10.0);
};