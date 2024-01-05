#pragma once
#include <vector>
#include "LightSource.hpp"
#include "SmoothObject.hpp"
#include "SimpleObject.hpp"

class Scene
{
private:
	std::vector<LightSource*> lightSources;
	std::vector<SmoothObject*> smoothObjects;
	std::vector<SimpleObject*> simpleObjects;
public:
	Scene();
	void LoadModels();
	std::vector<SmoothObject*> getSmoothObjects();
	std::vector<SimpleObject*> getSimpleObjects();
	std::vector<LightSource*> getLightSources();

};