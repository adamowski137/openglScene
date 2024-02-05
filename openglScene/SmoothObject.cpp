#include "SmoothObject.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include <glm/glm.hpp>
#include <iostream>

SmoothObject::SmoothObject(int trianglesRow, glm::vec3 position, const char* path):
	Object{position, path}, trianglesRow{ trianglesRow}, ebo{}
{
	for (int i = 0; i < CONTROLPOINTSROW; i++)
	{
		for (int j = 0; j < CONTROLPOINTSROW; j++)
		{
			controlPoints[i][j] = 0.0f;
			velocity[i][j] = ((rand() % 100) - 50) / 300.0f;
		}
	}
	vao.bindVAO();
	vbo.bindVBO();
	ebo.bindEBO();
	int n = getVAOSize();
	float* vert = getObjectVAO();
	unsigned int* eboData = getEBO();
	
	glBufferData(GL_ARRAY_BUFFER, n, vert, GL_STREAM_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, trianglesRow * trianglesRow * 6 * sizeof(unsigned int), eboData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 9, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 9, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 9, (void*)(sizeof(float) * 6));
	delete[] vert;
	delete[] eboData;
}

SmoothObject::~SmoothObject()
{
	delete[] controlPoints;
}

int SmoothObject::getVertexSize()
{
	return trianglesRow * trianglesRow * 3 * 2;
}

glm::mat4 SmoothObject::getModel()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3{ 2.0f, 1.0f, 3.5f });
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3{ 1.0f, 0.0f, 0.0f });
	return model;
}

void SmoothObject::renderObject()
{
	vao.bindVAO();
	glDrawElements(GL_TRIANGLES, trianglesRow * trianglesRow * 6, GL_UNSIGNED_INT, 0);
}

void SmoothObject::animate(float dt)
{
	for (int i = 0; i < CONTROLPOINTSROW; i++)
	{
		for (int j = 0; j < CONTROLPOINTSROW; j++)
		{
			if (controlPoints[i][j] > 1.0f) velocity[i][j] *= -1;
			if (controlPoints[i][j] < -1.0f) velocity[i][j] *= -1;

			controlPoints[i][j] += velocity[i][j] * dt;
		}
	}

	vao.bindVAO();
	vbo.bindVBO();
	int n = getVAOSize();
	float* vert = getObjectVAO();
	glBufferData(GL_ARRAY_BUFFER, n, vert, GL_STREAM_DRAW);
	delete vert;
}


int SmoothObject::getVAOSize()
{
	return (trianglesRow + 1) * (trianglesRow + 1) * 9 * sizeof(float);
}

float* SmoothObject::getObjectVAO()
{
	int n = (trianglesRow + 1) * (trianglesRow + 1) * 9;
	float* VAO = new float[n];
	for (int i = 0; i <= trianglesRow; i++)
	{
		for (int j = 0; j <= trianglesRow; j++)
		{
			int index = i * (trianglesRow + 1) + j;
			if (9 * index + 8 >= n) 
				break;
			float h = 0.00001f;

			float x = static_cast<float>(j) * (1.0f / static_cast<float>(trianglesRow));
			float y = static_cast<float>(i) * (1.0f / static_cast<float>(trianglesRow));
			
			float z = calculateZ(x, y);
			float dx = calculateZ(x + h, y);
			float dy = calculateZ(x, y + h);
			float dzdx = (z - dx) / h;
			float dzdy = (z - dy) / h;

			glm::vec3 norm = glm::normalize(glm::cross(glm::vec3{ 1.0f, 0, dzdx }, glm::vec3{ 0, 1.0f, dzdy }));
			VAO[9 * index] = x;
			VAO[9 * index + 1] = y;
			VAO[9 * index + 2] = calculateZ(x, y);
			VAO[9 * index + 3] = -norm.x;
			VAO[9 * index + 4] = -norm.y;
			VAO[9 * index + 5] = -norm.z;
			VAO[9 * index + 6] = 1.0f;
			VAO[9 * index + 7] = 0.0f;
			VAO[9 * index + 8] = 0.0f;
		}
	}
	return VAO;
}

float SmoothObject::B(int i, float t)
{
	float c = 0.0f;
	if (i == 0) c = 1.0f;
	if (i == 1) c = 3.0f;
	if (i == 2) c = 3.0f;
	if (i == 3) c = 1.0f;

	return c * powf(t, i) * powf(1.0f - t, 3 - i);
}

float SmoothObject::calculateZ(float x, float y)
{
	float sum = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sum += controlPoints[i][j] * B(i, x) * B(j, y);
		}
	}
	return sum;
}

unsigned int* SmoothObject::getEBO()
{
	int n = trianglesRow * trianglesRow * 2 * 3;
	unsigned int* data = new unsigned int[n];
	for (int i = 0; i < trianglesRow; i++)
	{
		for (int j = 0; j < trianglesRow; j++)
		{
			int idx = i * (trianglesRow) + j;
			int cur = i * (trianglesRow + 1) + j;
			int nextX = i * (trianglesRow + 1) + j + 1;
			int nextY = (i + 1) * (trianglesRow + 1) + j;
			int nextXY = (i + 1) * (trianglesRow + 1) + j + 1;

			data[(6 * idx)] = cur;
			data[(6 * idx) + 1] = nextX;
			data[(6 * idx) + 2] = nextY;
			data[(6 * idx) + 3] = nextXY;
			data[(6 * idx) + 4] = nextX;
			data[(6 * idx) + 5] = nextY;
		}
	}
	return data;
}

