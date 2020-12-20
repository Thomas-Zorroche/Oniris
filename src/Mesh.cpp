#include "Mesh.hpp"
#include "common.hpp"
#include "Shader.h"
#include "Texture.h"
#include <string>
#include <iostream>
#include "Material.hpp"
#include "ResourceManager.hpp"

Mesh::Mesh(const std::vector<ShapeVertex>& vertices, const std::shared_ptr<Material>& material,
           const std::vector<unsigned int>& indices)
    : _vertices(vertices), _material(material), _indices(indices)
{
    SetupMesh();
}

Mesh::Mesh()
    : _vertices(std::vector<ShapeVertex>()), 
      _material(ResourceManager::Get().CachePBRColorMaterial("Default", glm::vec3(1.0, 1.0, 1.0))),
      _indices(std::vector<unsigned int>())
{

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

    // Textures 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (unsigned int i = 0; i < _material->TextureCount(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); 

        std::string typeStr;
        switch (i)
        {
        case 0:
            typeStr = "u_Diffuse";
            break;
        case 1:
            typeStr = "u_Roughness";
            break;
        case 2:
            typeStr = "u_Normal";
            break;
        case 3:
            typeStr = "u_Heightmap";
            break;
        default:
            break;
        }
        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader->getID(), typeStr.c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, _material->GetParameterTexture(i));
    }

    //
    // [TODO 1] :: Lien entre Material Basic Color and Shader
    //

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