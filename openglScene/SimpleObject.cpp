#include "SimpleObject.hpp"

SimpleObject::SimpleObject(std::vector<glm::vec3> coordinates, std::vector<glm::vec3> color, std::vector<glm::vec2> texture, glm::vec3 position)
	: coordinates{ coordinates }, color{ color }, texture{ texture } 
{
	this->position = position;
}

int SimpleObject::getVertexSize()
{
	return coordinates.size();
}

int SimpleObject::getVAOSize()
{
	return 8 * coordinates.size();
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
