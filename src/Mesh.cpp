#include "Mesh.hpp"
#include "common.hpp"
#include "Shader.h"


Mesh::Mesh(std::vector<ShapeVertex> vertices)
	: _vertices(vertices)
{
	SetupMesh();
}

void Mesh::SetupMesh()
{
    // Generate Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(ShapeVertex), &_vertices[0], GL_STATIC_DRAW);

    // Vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (void*)offsetof(ShapeVertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (void*)offsetof(ShapeVertex, texCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader)
{
    // TO DO : Textures 
    // ...

    // draw mesh
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    glBindVertexArray(0);

}