#pragma once
#include "Object.hpp"

class SimpleObject : public Object
{
	std::vector<glm::vec3> coordinates;
	std::vector<glm::vec3> color;
	std::vector<glm::vec2> texture;

public:
	SimpleObject(std::vector<glm::vec3> coordinates, std::vector<glm::vec3> color, std::vector<glm::vec2> texture, glm::vec3 position);
	int getVertexSize()  override;
	int getVAOSize() override;
	float* getObjectVAO() override;
};
