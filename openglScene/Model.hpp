#pragma once
#include <vector>
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model(const char* file, glm::vec3 position, bool gamma = false);
	void renderObject(const Shader& shader);
	glm::mat4 getModel();
	void animate(float dt);
	glm::vec3 position;
	glm::vec3 direction;
private:
	bool gammaCorrection;
	std::vector<Mesh*> meshes;
	std::string directory;
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
};