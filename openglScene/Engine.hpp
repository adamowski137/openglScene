#pragma once
#include <vector>
#include "SmoothObject.hpp"
#include "SimpleObject.hpp"
class Engine 
{
private:
	int width;
	int height;
	std::vector<SmoothObject*> smoothObjects;
	std::vector<SimpleObject*> simpleObjects;


	void loadModels();
	void setOneTimeShaderData();
public:
	const Shader simpleObjectShader;
	const Shader smoothObjectShader;

	Engine(int width, int height);
	~Engine();

	void render(glm::mat4 view);
};