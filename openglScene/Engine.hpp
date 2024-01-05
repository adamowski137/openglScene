#pragma once
#include <vector>
#include "SmoothObject.hpp"
#include "SimpleObject.hpp"
#include "Scene.hpp"
class Engine 
{
private:
	int width;
	int height;
	Scene scene;

	void setOneTimeShaderData();
	void setLightData(std::vector<LightSource*> lights, const Shader& shader);
public:
	const Shader simpleObjectShader;
	const Shader smoothObjectShader;
	const Shader lightObjectShader;

	Engine(int width, int height);
	~Engine();

	void render(glm::mat4 view, glm::vec3 position);
};