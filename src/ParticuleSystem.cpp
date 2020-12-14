#include "ParticuleSystem.hpp"

#include <glad/glad.h>

#include "SpecialMesh.hpp"
#include "ResourceManager.hpp"
#include "Texture.h"
#include "Terrain.hpp"
#include "Renderer.hpp"

#include "glm/glm.hpp"

#include <string>
#include <random>
#include <chrono>


ParticuleSystem::ParticuleSystem(const std::string& name, const StaticMesh& mesh, unsigned int count,
    const std::vector<ControlPointParticule>& controlPoints, std::shared_ptr<Terrain>& terrain)
	: _name(name), _instance(mesh), _instanceVAO(mesh.GetVAO()), _count(count), _controlPoints(controlPoints), _terrain(terrain)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    
    std::vector<glm::vec3> translations;
    std::vector<float> scales;
    
    for (size_t i = 0; i < _controlPoints.size(); i++)
    {
        double meanX = _controlPoints[i].Position().x;
        double meanZ = _controlPoints[i].Position().y;
        double stdev = _controlPoints[i].Radius();
        std::normal_distribution<double> normalDistributionX(meanX, stdev);
        std::normal_distribution<double> normalDistributionZ(meanZ, stdev);
        
        // Random Positions
        for (size_t i = 0; i < _count / (float)_controlPoints.size(); i++)
        {
            glm::vec3 trans;
            trans.x = normalDistributionX(generator);
            trans.z = normalDistributionZ(generator);
            trans.y = _terrain->GetHeightOfTerrain(trans.x, trans.z);
            translations.push_back(trans);
        }

        // Random Scales
        std::uniform_int_distribution<int> uniformIntDistribution(2, 4);
        for (size_t i = 0; i < _count / (float)_controlPoints.size(); i++)
        {
            scales.push_back(uniformIntDistribution(generator));
        }
    }


    // Instanced Array Attribute
    glBindVertexArray(_instanceVAO);
    unsigned int vboTrans, vboScales;

    glGenBuffers(1, &vboTrans);
    glBindBuffer(GL_ARRAY_BUFFER, vboTrans);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _count, &translations[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(3, 1);

    glGenBuffers(1, &vboScales);
    glBindBuffer(GL_ARRAY_BUFFER, vboScales);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _count, &scales[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)(0));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(4, 1);
    glBindVertexArray(0);
}

void ParticuleSystem::Draw()
{
    Renderer::Get().SendBlinnPhongUniforms(_instance.GetShader()); 
    auto shader = _instance.GetShader();
    shader->Bind();
    shader->SetUniform3f("u_SkyColor", 0.32f, 0.78f, 0.76f);

    _instance.Draw(true, _count);
}