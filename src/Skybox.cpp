#include "Skybox.hpp"




Skybox::Skybox(const std::vector<std::string>& faces)
    : _faces(faces),
      _id(ResourceManager::Get().LoadCubemap(_faces)),
      _shader(ResourceManager::Get().GetShader("Skybox"))
{
    GenerateMesh();
}


void Skybox::GenerateMesh()
{
    std::cout << "Generate Skybox" << std::endl;
    std::vector<ShapeVertex> vertices;
    int index = 0;
    for (size_t i = 0; i < 36; i++)
    {
        ShapeVertex vertex;
        vertex.position.x = _SkyboxVertices[index++];
        vertex.position.y = _SkyboxVertices[index++];
        vertex.position.z = _SkyboxVertices[index++];

        vertex.normal.x = 1;
        vertex.normal.y = 1;
        vertex.normal.z = 1;

        vertex.texCoords.x = 0;
        vertex.texCoords.y = 0;

        vertices.push_back(vertex);
    }
    _mesh = std::make_shared<Mesh>(vertices, std::make_shared<Material>());
}

void Skybox::Draw()
{
    glDepthMask(GL_FALSE);

   /* glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);*/

    // Set uniform
    // -----------
    _shader->Bind();
    Renderer::Get().SendModelMatrixUniforms(glm::mat4(1.0f), _shader, true);
    glBindVertexArray(_mesh->GetVAO());

    // Active Texture
    // --------------
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
    //glUniform1i(glGetUniformLocation(_shader->getID(), "skybox"), 0);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //glDisable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glDepthMask(GL_TRUE);

    _shader->Unbind();
}



// Just a simple cube, no TexCoords needed
// ---------------------------------------
const float Skybox::_SkyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};


