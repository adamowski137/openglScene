#pragma once
#include "Object.hpp"
#include <glm/glm.hpp>

class SmoothObject : public Object
{
private:
	float* controlPoints;
	int controlPointsRow;
	int controlPointsColumn;

	std::vector<glm::vec3> generateGrid();
	int getVAOSize() override;
	float* getObjectVAO() override;
public:
	SmoothObject(int controlPointsRow, int controlPointsColumn, glm::vec3 position, const char* path);
	~SmoothObject();
	int getVertexSize();
	void renderObject() override;
};