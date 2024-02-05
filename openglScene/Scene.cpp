#include "Scene.hpp"
#include "Utils.hpp"
Scene::Scene()
{
	loadModels();
}

void Scene::loadModels()
{
	smoothObjects.push_back(Utils::generateBezier(glm::vec3(0.0f, 0.0f, 0.0f), "wall.jpg", 100));
	simpleObjects.push_back(Utils::generateBox(glm::vec3(1.0f, 2.0f, 0.0f), "wall.jpg"));
	lightSources.push_back(Utils::generateLightSource(glm::vec3{ 2.0f, 5.0f, 2.0f }));
	lightSources.push_back(Utils::generateLightSource(glm::vec3{ 5.0f, 7.5f, 3.5f }));
	models.push_back(new Model{ "objects/bench/bench.obj", glm::vec3{4.0f, 2.0f, 4.0f} });
	models.push_back(new Model{ "objects/bench/bench.obj", glm::vec3{10.0f, 1.0f, 4.0f} });
	models.push_back(new Model{ "objects/m4a1/m4a1_s.obj", glm::vec3{0.0f, 2.0f, 3.0f} });
	models.push_back(new Model{ "objects/car/Car.obj", glm::vec3{12.0f, 2.0f, -3.0f} });
	models.push_back(new Model{ "objects/car/Car.obj", glm::vec3{4.0f, 2.0f, 5.0f} });

	specialObject = new Model{ "objects/car/Car.obj", glm::vec3{2.0f, 2.0f, 5.0f} };
	specialObjectReflectorLeft.position = specialObject->position;
	specialObjectReflectorLeft.color = glm::vec3{ 1.0f, 1.0f, 1.0f };
	specialObjectReflectorLeft.direction = glm::vec3{ 1.0f, 1.0f, 1.0f };
	specialObjectReflectorLeft.cutOff = glm::radians(12.5f);

	specialObjectReflectorRight.position = specialObject->position;
	specialObjectReflectorRight.color = glm::vec3{ 1.0f, 1.0f, 1.0f };
	specialObjectReflectorRight.direction = glm::vec3{ -1.0f, 1.0f, 1.0f };
	specialObjectReflectorRight.cutOff = glm::radians(12.5f);
}

void Scene::setLightColor(glm::vec3 color)
{
	for (auto& l : lightSources)
	{
		l->setColor(color);
	}
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

std::vector<Model*> Scene::getModels()
{
	return models;
}
