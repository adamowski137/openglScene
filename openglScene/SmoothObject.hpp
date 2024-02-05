#pragma once
#include "Object.hpp"
#include <glm/glm.hpp>
#include "EBO.hpp"

#define CONTROLPOINTSROW 4

class SmoothObject : public Object
{
private:
	int trianglesRow;
	EBO ebo;

	int getVAOSize() override;
	float* getObjectVAO() override;
	float B(int i, float t);
	float calculateZ(float x, float y);
	unsigned int* getEBO();
	
	float controlPoints[CONTROLPOINTSROW][CONTROLPOINTSROW];
	float velocity[CONTROLPOINTSROW][CONTROLPOINTSROW];
public:
	SmoothObject(int trianglesRow, glm::vec3 position, const char* path);
	~SmoothObject();
	int getVertexSize();
	glm::mat4 getModel() override;
	void renderObject() override;
	void animate(float dt);
};