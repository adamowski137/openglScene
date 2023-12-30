#pragma once
#include "Object.hpp"
#include <glm/glm.hpp>

class SmoothObject : public Object
{
private:
	float* controlPoints;
	int controlPointsRow;
	int controlPointsColumn;
	int amountOfTrianglesRow;
	int amountOfTrianglesColumn;

	std::vector<glm::vec3> generateGrid();
	float calculateZ(float x, float y);
	float B(int i, int n, float t);
	int getVAOSize() override;
	float* getObjectVAO() override;
public:
	SmoothObject(int controlPointsRow, int controlPointsColumn, int amountOfTrianglesRow, int amountOfTrianglesColumn, glm::vec3 position, const char* path);
	~SmoothObject();
	int getVertexSize();
};