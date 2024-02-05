#pragma once
#include <vector>
#include "LightSource.hpp"
#include "SmoothObject.hpp"
#include "SimpleObject.hpp"
#include "Model.hpp"

class Scene
{
private:
	std::vector<LightSource*> lightSources;
	std::vector<SmoothObject*> smoothObjects;
	std::vector<SimpleObject*> simpleObjects;
	std::vector<Model*> models;
public:
	Scene();
	void loadModels();
	void setLightColor(glm::vec3 color);
	std::vector<SmoothObject*> getSmoothObjects();
	std::vector<SimpleObject*> getSimpleObjects();
	std::vector<LightSource*> getLightSources();
	std::vector<Model*> getModels();
	Model* specialObject;
	ReflectorArguments specialObjectReflectorLeft;
	ReflectorArguments specialObjectReflectorRight;
};