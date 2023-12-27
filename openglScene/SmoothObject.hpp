#pragma once
#include "Object.hpp"

class SmoothObject : public Object
{
private:
	float* controlPoints;
	int controlPointsNumber;
	int amountOfTriangles;
public:
	SmoothObject(int controlPointsNumber, int amountOfTriangles);
	~SmoothObject();
};