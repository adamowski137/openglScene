#include "Scene.hpp"
#include "Utils.hpp"
Scene::Scene()
{
	LoadModels();
}

void Scene::LoadModels()
{
	smoothObjects.push_back(Utils::generateBezier(glm::vec3(0.0f, 0.0f, 0.0f), "wall.jpg", 4));
	simpleObjects.push_back(Utils::generateBox(glm::vec3(1.0f, 2.0f, 0.0f), "wall.jpg"));
	lightSources.push_back(Utils::generateLightSource(glm::vec3{2.0f, 2.0f, 2.0f}));
	//lightSources.push_back(Utils::generateLightSource(glm::vec3{ 1.0f, 1.5f, 1.5f }));

}

std::vector<SmoothObject*> Scene::getSmoothObjects()
{
	return smoothObjects;
}

std::vector<SimpleObject*> Scene::getSimpleObjects()
{
	return simpleObjects;
}

std::vector<LightSource*> Scene::getLightSources()
{
	return lightSources;
}
