#pragma once

#include <vector>
#include <string>
#include "glm/glm.hpp"

#include "opengl/Mesh.hpp"
#include "opengl/Texture.h"
#include "opengl/Shader.h"

class Material;
class Fog;

class Terrain
{
public:
	// Constructor
	Terrain(float x, float z, const std::string& heightmapPath);
	
	float GetHeightmapValue(int x, int y) const;
	double GetHeightOfTerrain(int worldX, int worldZ) const;
	float GetHeightSmooth(float x, float z);
	glm::vec3 GetNormal(int worldX, int worldZ) const;

	std::shared_ptr<Shader>& GetShader() { return _shader; }

	void Draw(const std::shared_ptr<Fog>& fog);
	void SendUniforms(const std::shared_ptr<Fog>& fog);

private:
	static const float _Size;
	static const float _MaxHeight;

	float   _height = 0.0f;
	float   _x;
	float   _z;
	std::vector<unsigned short> _dataHeightmap;

	std::vector<std::vector<float>> _heights;
	std::vector<std::vector<glm::vec3>> _normals;

	Mesh    _mesh;
	int     _VertexSideCount;
	float   _GridSquareSize;

	std::shared_ptr<Material> _material;
	std::shared_ptr<Shader> _shader;

	Mesh generateMesh();
	glm::vec3 CalculateNormals(int x, int z);
};