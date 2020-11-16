#shader vertex
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

void main() {
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    vPosition_vs = vec3(uMVMatrix * vertexPosition);
    vNormals_vs = vec3(uNormalMatrix * vertexNormal);
    vVertexTexcoords = aVertexTexcoords;

    gl_Position = uMVPMatrix * vertexPosition;
}

#shader fragment
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
