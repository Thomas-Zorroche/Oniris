#include "opengl/Mesh.hpp"
#include "common.hpp"
#include "opengl/Shader.h"
#include "opengl/Texture.h"
#include <string>
#include <iostream>
#include "engine/Material.hpp"
#include "engine/ResourceManager.hpp"

Mesh::Mesh(const std::vector<ShapeVertex>& vertices, const std::shared_ptr<Material>& material,
           const std::vector<unsigned int>& indices)
    : _vertices(vertices), _material(material), _indices(indices)
{
    SetupMesh();
}

void Mesh::Free()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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

void Mesh::Draw(std::shared_ptr<Shader>& shader, bool IsParticuleInstance, int countParticules) const
{
    shader->Bind();

    _material->SendMaterialUniform(shader);

    // Textures 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (_material->TextureCount() > 0)
    {
        glActiveTexture(GL_TEXTURE0); 
        glBindTexture(GL_TEXTURE_2D, _material->GetParameterTexture(0));
    }

    // draw mesh
    glBindVertexArray(VAO);
    if (IsParticuleInstance)
    {
        glDrawElementsInstanced(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0, countParticules);
    }
    else if (_indices.empty())
        glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    else
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    shader->Unbind();
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_BLEND);

}