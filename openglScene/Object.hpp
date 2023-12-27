#pragma once
#include <vector>
#include <glm/glm.hpp>


class Object 
{
public:
	glm::vec3 position;
	virtual int getVertexSize() = 0;
	virtual int getVAOSize() = 0;
	virtual float* getObjectVAO() = 0;
};