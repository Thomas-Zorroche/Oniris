# pragma once 

#include <vector>
#include <string>
#include <memory>

#include "Mesh.hpp"
#include "Texture.h"
#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	// Constructor
	Model(const std::string& path);
	void Model::Draw(std::shared_ptr<Shader>& shader, bool isParticuleInstance = false, int countParticule = 0);

	// Retrieve mesh vbo (when there is a single mesh in the model)
	// Useful for particule system
	unsigned int GetVAO() const { return _meshes[0].GetVAO(); }

private:
	std::vector<Mesh> _meshes;
	std::string _directory;
	std::vector<Texture> _textures_loaded;


	void LoadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};