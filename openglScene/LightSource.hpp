#pragma once
#include <glm/glm.hpp>
#include "Object.hpp"

struct LightArguments {
	glm::vec3 position;
	glm::vec3 color;
	float strength;
};

struct ReflectorArguments {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 direction;
	float cutOff;
};

class LightSource : public Object
{
private:
	LightArguments lightArgs;
	std::vector<glm::vec3> coordinates;
	int getVAOSize() override;
	float* getObjectVAO() override;

public:
	LightSource(LightArguments args, std::vector<glm::vec3> coordinates);
	LightArguments getLightArguments();
	int getVertexSize()	override;
	void renderObject() override;
	void setColor(glm::vec3 color);
};