#include "SmoothObject.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include <glm/glm.hpp>
#include <iostream>

SmoothObject::SmoothObject(int controlPointsRow, int controlPointsColumn, int amountOfTrianglesRow, 
	int amountOfTrianglesColumn, glm::vec3 position, const char* path):
	Object{position, path},
	controlPointsRow{ controlPointsRow },
	controlPointsColumn { controlPointsColumn },
	amountOfTrianglesRow{ amountOfTrianglesRow },
	amountOfTrianglesColumn{amountOfTrianglesColumn}
{
	controlPoints = new float[controlPointsRow * controlPointsColumn];
	for (int i = 0; i < controlPointsRow * controlPointsColumn; i++)
	{
		controlPoints[i] = (rand() % 157) / 157.0f;
	}
	int n = getVAOSize();
	float* vert = getObjectVAO();
	vao.bufferData(n, vert, GL_STATIC_DRAW);
	delete vert;
}

SmoothObject::~SmoothObject()
{
	delete controlPoints;
}

int SmoothObject::getVertexSize()
{
	return amountOfTrianglesRow * amountOfTrianglesColumn;
}

std::vector<glm::vec3> SmoothObject::generateGrid()
{
	std::vector<glm::vec3> grid{};

	for (int i = 0; i < (amountOfTrianglesColumn - 1); i++)
	{
		float y = static_cast<float>(i) * (1.0f / static_cast<float>(amountOfTrianglesColumn));
		float ynext = static_cast<float>(i+1) * (1.0f / static_cast<float>(amountOfTrianglesColumn));
		for (int j = 0; j < amountOfTrianglesRow - 1; j++)
		{
			float x = static_cast<float>(j) * (1.0f / static_cast<float>(amountOfTrianglesRow));
			float xnext = static_cast<float>(j+1) * (1.0f / static_cast<float>(amountOfTrianglesRow));
			grid.push_back(glm::vec3{ x, calculateZ(x, y), y});
			grid.push_back(glm::vec3{ x, calculateZ(x, ynext), ynext });
			grid.push_back(glm::vec3{ xnext, calculateZ(xnext, y), y });

			grid.push_back(glm::vec3{ xnext, calculateZ(xnext, ynext), ynext });
			grid.push_back(glm::vec3{ x, calculateZ(x, ynext), ynext });
			grid.push_back(glm::vec3{ xnext, calculateZ(xnext, y), y});
		}
	}

	return grid;
}

float SmoothObject::calculateZ(float x, float y)
{
	int n = controlPointsRow * controlPointsColumn;
	float sum = 0.0f;
	for (int i = 0; i < controlPointsRow; i++)
	{
		for(int j = 0; j < controlPointsColumn; j++)
		{
			sum += controlPoints[i + j * controlPointsRow] * B(i, controlPointsRow, x) * B(j, controlPointsColumn, y);
		}
	}

	return fmaxf(0.0f, fminf(1.0f, sum));
}

float SmoothObject::B(int i, int n, float t)
{
	float fn = static_cast<float>(n);
	float fi = static_cast<float>(i);

	float r = (tgammaf(fn) / (tgammaf(fn - fi) * tgammaf(fi))) * powf(t, fi) * powf(1 - t, fn - fi);
	return r;
}

int SmoothObject::getVAOSize()
{
	return amountOfTrianglesRow * amountOfTrianglesColumn * 8 * sizeof(float);
}

float* SmoothObject::getObjectVAO()
{
	auto points = generateGrid();
	int n = points.size();
	float* VAO = new float[8 * n];
	
	for (int i = 0; i < n; i++)
	{
		VAO[8 * i] = points[i].x;
		VAO[8 * i + 1] = points[i].y;
		VAO[8 * i + 2] = points[i].z;
		VAO[8 * i + 3] = 1.0f;
		VAO[8 * i + 4] = 0.0f;
		VAO[8 * i + 5] = 0.0f;
		VAO[8 * i + 6] = 0.0f;
		VAO[8 * i + 7] = 1.0f;
	}

	return VAO;
}

