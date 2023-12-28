#include "SmoothObject.hpp"

std::vector<glm::vec3> SmoothObject::generateGrid()
{
	std::vector<glm::vec3> grid{};
	for (int i = 0; i < amountOfTrianglesColumn - 1; i++)
	{
		float y = static_cast<float>(i) * (1.0f / static_cast<float>(amountOfTrianglesColumn));
		float ynext = static_cast<float>(i+1) * (1.0f / static_cast<float>(amountOfTrianglesColumn));
		for (int j = 0; j < amountOfTrianglesRow - 1; j++)
		{
			float x = static_cast<float>(j) * (1.0f / static_cast<float>(amountOfTrianglesRow));
			float xnext = static_cast<float>(j+1) * (1.0f / static_cast<float>(amountOfTrianglesRow));
			grid.push_back(glm::vec3{ x, y, });

		}
	}
}

SmoothObject::SmoothObject(int controlPointsNumber, int amountOfTrianglesRow, int amountOfTrianglesColumn): 
	controlPointsNumber{ controlPointsNumber }, 
	amountOfTrianglesRow{ amountOfTrianglesRow },
	amountOfTrianglesColumn{amountOfTrianglesColumn}
{
	controlPoints = new float[controlPointsNumber];
}

SmoothObject::~SmoothObject()
{
	delete controlPoints;
}