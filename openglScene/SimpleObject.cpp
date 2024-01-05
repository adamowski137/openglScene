#include "SimpleObject.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

SimpleObject::SimpleObject(std::vector<glm::vec3> coordinates, std::vector<glm::vec3> color, 
	std::vector<glm::vec2> texture, glm::vec3 position, const char* path)
	: Object{position, path}, coordinates { coordinates }, color{ color }, texture{ texture }
{
	int n = getVAOSize();
	float* vert = getObjectVAO();
	vao.bufferData(n, vert, GL_STATIC_DRAW);
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
	return 8 * coordinates.size() * sizeof(float);
}

float* SimpleObject::getObjectVAO()
{
	const int n = coordinates.size();

	float* array = new float[8 * n];
	for (int i = 0; i < n; i++)
	{
		array[8 * i] = coordinates[i].x;
		array[8 * i + 1] = coordinates[i].y;
		array[8 * i + 2] = coordinates[i].z;
		array[8 * i + 3] = color[i].r;
		array[8 * i + 4] = color[i].g;
		array[8 * i + 5] = color[i].b;
		array[8 * i + 6] = texture[i].x;
		array[8 * i + 7] = texture[i].y;
	}

	return array;
}
