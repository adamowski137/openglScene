#include "SmoothObject.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include <glm/glm.hpp>
#include <iostream>

SmoothObject::SmoothObject(int controlPointsRow, int controlPointsColumn, glm::vec3 position, const char* path):
	Object{position, path},
	controlPointsRow{ controlPointsRow },
	controlPointsColumn { controlPointsColumn }
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
	return controlPointsRow * controlPointsColumn;
}

void SmoothObject::renderObject()
{
	vao.bindVAO();
	bindTexture();
	glDrawArrays(GL_PATCHES, 0, getVertexSize());
}

std::vector<glm::vec3> SmoothObject::generateGrid()
{
	std::vector<glm::vec3> points;
	for (int i = 0; i < (controlPointsColumn); i++)
	{
		float y = static_cast<float>(i) * (1.0f / static_cast<float>(controlPointsColumn - 1));
		for (int j = 0; j < controlPointsRow; j++)
		{
			float x = static_cast<float>(j) * (1.0f / static_cast<float>(controlPointsRow - 1));
			points.push_back(glm::vec3{ x, y, controlPoints[i * controlPointsRow + j]});
		}
	}

	return points;
}


int SmoothObject::getVAOSize()
{
	return controlPointsRow * controlPointsColumn * 8 * sizeof(float);
}

float* SmoothObject::getObjectVAO()
{
	auto points = generateGrid();
	int n = controlPointsColumn * controlPointsRow;
	float* VAO = new float[8 * n];
	
	for (int i = 0; i < n; i++)
	{
		VAO[8 * i] = points[i].x;
		VAO[8 * i + 1] = points[i].y;
		VAO[8 * i + 2] = points[i].z;
		VAO[8 * i + 3] = 1.0f;
		VAO[8 * i + 4] = 0.0f;
		VAO[8 * i + 5] = 0.0f;
		VAO[8 * i + 6] = points[i].x;
		VAO[8 * i + 7] = points[i].y;
	}

	return VAO;
}

