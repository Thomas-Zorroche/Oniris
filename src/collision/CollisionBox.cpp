#include "collision/CollisionBox.hpp"
#include "engine/ShapeCube.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/Renderer.hpp"
#include "opengl/Mesh.hpp"
#include "glm/glm.hpp"

CollisionBox::CollisionBox(const glm::vec3& origin, float w, float h, float d,
    const CollisionLayout& cLayout)
	: _x(origin.x), _y(origin.y), _z(origin.z), _w(w), _h(h), _d(d), 
      _debugMesh(ShapeCube(glm::vec3(_x, _y, _z), _w, _h, _d).Vertices(), 
                 ResourceManager::Get().CachePBRColorMaterial("cubeDebug", glm::vec3(1, 0, 0)), 
                 ShapeCube(glm::vec3(_x, _y, _z), _w, _h, _d).Indices()),
     _cLayout(cLayout)
{
    //updateDebugMesh();
}

void CollisionBox::OnBeginOverlap()
{
    _cLayout.Function();
}

// Check whether the box overlaps with another box
HitResult CollisionBox::IsColliding(const std::shared_ptr<CollisionBox>& box)
{
    if ((box->_x > _x + _w)            // trop à droite 
        || (box->_x + box->_w < _x)    // trop à gauche 
        || (box->_y > _y + _h)         // trop en bas 
        || (box->_y + box->_h < _y)    // trop en haut     
        || (box->_z < _z - _d)         // trop derrière 
        || (box->_z - box->_d > _z))   // trop devant 
        return { false, NONE };
    else
    {
        // if cBox blocks the mouvement, find the correct axis
        if (_cLayout.CanStopMovement())
        {
            if (box->_z - box->_d <= _z - _d)
                return { true, Z_POS };
            if (box->_z >= _z)
                return { true, Z_NEG };
            if (box->_x <= _x)
                return { true, X_POS };
            if (box->_x + box->_w >= _x + _w)
                return { true, X_NEG };
        }
        
        return { true, NONE };
    }
}

void CollisionBox::AddIndex(CollisionGridCase gridCase, int index)
{
    _indices.insert({ gridCase, index });
}

void CollisionBox::DecreaseIndexCase(CollisionGridCase gridCase)
{
    _indices[gridCase] -= 1;
}

void CollisionBox::updateDebugMesh()
{
    ShapeCube debugShape(ShapeCube(glm::vec3(_x, _y, _z), _w, _h, _d));
    _debugMesh = Mesh(debugShape.Vertices(), ResourceManager::Get().CachePBRColorMaterial("cubeDebug", glm::vec3(1, 0, 0)), debugShape.Indices());
}

void CollisionBox::Draw()
{
    auto shader = ResourceManager::Get().GetShader("CBox");
    shader->Bind();

    Renderer::Get().SendTransMatrixUniforms(glm::mat4(1.0f), shader);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    _debugMesh.Draw(ResourceManager::Get().GetShader("CBox"));
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    shader->Unbind();
}



