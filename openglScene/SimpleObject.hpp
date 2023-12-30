#pragma once
#include "Object.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "Shader.hpp"


class SimpleObject : public Object
{
private:
	std::vector<glm::vec3> coordinates;
	std::vector<glm::vec3> color;
	std::vector<glm::vec2> texture;
	int getVAOSize() override;
	float* getObjectVAO() override;

public:
	SimpleObject(std::vector<glm::vec3> coordinates, std::vector<glm::vec3> color, std::vector<glm::vec2> texture, glm::vec3 position, const char* path);
	int getVertexSize()	override;
};
