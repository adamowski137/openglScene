#include "LightSource.hpp"

LightSource::LightSource(LightArguments args, std::vector<glm::vec3> coordinates)
	: Object{args.position, NULL}, coordinates{coordinates}
{
	lightArgs = args;
	int n = getVAOSize();
	float* vert = getObjectVAO();
	vao.bufferData(n, vert, GL_STATIC_DRAW);
	delete vert;
}

int LightSource::getVAOSize()
{
	return coordinates.size() * 8 * sizeof(float);
}

float* LightSource::getObjectVAO()
{
	const int n = coordinates.size();
	float* array = new float[8 * n];
	for (int i = 0; i < n; i++)
	{
		array[8 * i] = coordinates[i].x;
		array[8 * i + 1] = coordinates[i].y;
		array[8 * i + 2] = coordinates[i].z;
		array[8 * i + 3] = 0.0f;
		array[8 * i + 4] = 0.0f;
		array[8 * i + 5] = 0.0f;
		array[8 * i + 6] = 0.0f;
		array[8 * i + 7] = 0.0f;
	}
	return array;
}


LightArguments LightSource::getLightArguments()
{
	return lightArgs;
}

int LightSource::getVertexSize()
{
	return coordinates.size();
}

void LightSource::renderObject()
{
	vao.bindVAO();

	glDrawArrays(GL_TRIANGLES, 0, getVertexSize());
}
