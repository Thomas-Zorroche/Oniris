#include "Mesh.hpp"
#include "common.hpp"
#include "Shader.h"

#include <string>

Mesh::Mesh(const std::vector<ShapeVertex> & vertices, std::vector<unsigned int> * indices, std::vector<Texture> * textures)
	: _vertices(vertices)
{
    if (indices)
        _indices = *indices;
    if (textures)
        _textures = *textures;

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

    if (!_indices.empty())
    {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);
    }

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

void Mesh::Draw(Shader& shader) const
{
    shader.Bind();
    
    // Textures 
    unsigned int diffuseNr = 1;

    for (unsigned int i = 0; i < _textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = _textures[i].GetType();
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.getID(), (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, _textures[i].GetID());
    }

    // draw mesh
    glBindVertexArray(VAO);
    if (_indices.empty())
        glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    else
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    shader.Unbind();
    glActiveTexture(GL_TEXTURE0);
}