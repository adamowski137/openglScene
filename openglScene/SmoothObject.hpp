#pragma once
#include "Object.hpp"

class SmoothObject : public Object
{
private:
	float* controlPoints;
	int controlPointsNumber;
	int amountOfTrianglesRow;
	int amountOfTrianglesColumn;

	std::vector<glm::vec3> generateGrid();
public:
	SmoothObject(int controlPointsNumber, int amountOfTrianglesRow, int amountOfTrianglesColumn);
	~SmoothObject();
};