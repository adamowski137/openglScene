#include "SmoothObject.hpp"

SmoothObject::SmoothObject(int controlPointsNumber, int amountOfTriangles) : controlPointsNumber{ controlPointsNumber }, amountOfTriangles{ amountOfTriangles }
{
	controlPoints = new float[controlPointsNumber];
}

SmoothObject::~SmoothObject()
{
	delete controlPoints;
}