#pragma once
#include "SimpleObject.hpp"
#include "SmoothObject.hpp"
#include <glm/glm.hpp>
class Utils 
{
public:
	static SimpleObject* generateBox(glm::vec3 position, const char* texturePath);
	static SmoothObject* generateBezier(glm::vec3 position, const char* texturePath, int triangles);
};