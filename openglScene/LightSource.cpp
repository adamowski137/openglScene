#include "LightSource.hpp"

LightSource::LightSource(LightArguments args, std::vector<glm::vec3> coordinates)
	: Object{args.position, NULL}, coordinates{coordinates}
{
	lightArgs = args;
	int n = getVAOSize();
	float* vert = getObjectVAO();
	glBufferData(GL_ARRAY_BUFFER, n, &vert[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 6));
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

void LightSource::setColor(glm::vec3 color)
{
	lightArgs.color = color;
}
