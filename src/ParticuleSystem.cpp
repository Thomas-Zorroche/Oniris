#include "ParticuleSystem.hpp"

#include <glad/glad.h>

#include "SpecialMesh.hpp"
#include "ResourceManager.hpp"
#include "Texture.h"
#include "Terrain.hpp"

#include "glm/glm.hpp"

#include <string>
#include <random>
#include <chrono>


ParticuleSystem::ParticuleSystem(const StaticMesh& mesh, unsigned int count, const std::string& pathDensity, std::shared_ptr<Terrain>& terrain)
	: _instance(mesh), _instanceVAO(mesh.GetVAO()), _count(count), _terrain(terrain),
	  _densityTexture(ResourceManager::Get().LoadTexture("res/img/grass_diffuse.jpg", DENSITY))
{
    glm::vec3 translations[100];
    int index = 0;
    float offset = 25.0f;
    for (int z = 0; z < 20; z += 2)
    {
        for (int x = 0; x < 20; x += 2)
        {
            translations[index].x = (float)x * offset;
            translations[index].z = (float)z * offset;
            translations[index].y = _terrain->GetHeightOfTerrain(translations[index].x, translations[index].z);
            index++;
        }
    }

    // select seed from time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> uniformIntDistribution(4, 8);

    float scales[100];
    for (size_t i = 0; i < 100; i++)
    {
        scales[i] = uniformIntDistribution(generator);
    }


    // Instanced Array Attribute
    glBindVertexArray(_instanceVAO);
    unsigned int vboTrans, vboScales;

    glGenBuffers(1, &vboTrans);
    glBindBuffer(GL_ARRAY_BUFFER, vboTrans);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 100, &translations[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(3, 1);

    glGenBuffers(1, &vboScales);
    glBindBuffer(GL_ARRAY_BUFFER, vboScales);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 100, &scales[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)(0));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(4, 1);
    glBindVertexArray(0);

    //auto shader = _instance.GetShader();
    //shader->Bind();
    //for (unsigned int i = 0; i < 100; i++)
    //{
    //    shader->SetUniform2f(("offsets[" + std::to_string(i) + "]"), translations[i].x, translations[i].y);
    //}
}

void ParticuleSystem::Draw()
{
	_instance.Draw(true, _count);
}