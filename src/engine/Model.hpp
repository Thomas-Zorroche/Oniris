# pragma once 

#include <vector>
#include <string>
#include <memory>

#include "opengl/Mesh.hpp"
#include "opengl/Texture.h"
#include "opengl/Shader.h"
#include "common.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	// Constructor
	Model(const std::string& path);
	void Model::Draw(std::shared_ptr<Shader>& shader, bool isParticuleInstance = false, int countParticule = 0);

	// Retrieve mesh vao (when there is a single mesh in the model)
	// Useful for particule system
	unsigned int GetVAO() const { return _meshes[0].GetVAO(); }

	std::vector<ShapeVertex>& Model::VerticesCBox(size_t index);

	std::vector<Mesh>& CBoxes() { return _cBoxes; }

	void Free();

private:
	std::vector<Mesh> _meshes;
	std::vector<Mesh> _cBoxes;
	std::string _directory;


	void LoadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene, bool IscBox);
};