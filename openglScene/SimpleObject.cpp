#include "SimpleObject.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

SimpleObject::SimpleObject(std::vector<glm::vec3> coordinates, std::vector<glm::vec3> color, 
	std::vector<glm::vec2> texture, glm::vec3 position, const char* path)
	: Object{position, path}, coordinates { coordinates }, color{ color }, texture{ texture }
{
	int n = getVAOSize();
	float* vert = getObjectVAO();
	vao.bindVAO();
	vbo.bindVBO();
	glBufferData(GL_ARRAY_BUFFER, n, vert, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 9, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 9, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 9, (void*)(sizeof(float) * 6));

	delete vert;
}

int SimpleObject::getVertexSize()
{
	return coordinates.size();
}

void SimpleObject::renderObject()
{
	vao.bindVAO();

	glDrawArrays(GL_TRIANGLES, 0, getVertexSize());
}

int SimpleObject::getVAOSize()
{
	return 9 * coordinates.size() * sizeof(float);
}

float* SimpleObject::getObjectVAO()
{
	const int n = coordinates.size();

	float* array = new float[9 * n];
	for (int i = 0; i < n; i++)
	{
		array[9 * i] = coordinates[i].x;
		array[9 * i + 1] = coordinates[i].y;
		array[9 * i + 2] = coordinates[i].z;
		array[9 * i + 3] = 0.0f;
		array[9 * i + 4] = 0.0f;
		array[9 * i + 5] = 0.0f;
		array[9 * i + 6] = color[i].r;
		array[9 * i + 7] = color[i].g;
		array[9 * i + 8] = color[i].b;
	}

	return array;
}
