#include "StaticCamera.hpp"

StaticCamera::StaticCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Camera { position, up, yaw, pitch }
{
}

StaticCamera::StaticCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Camera{ posX, posY, posZ, upX, upY, upZ, yaw, pitch }
{
	return;
}

void StaticCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	return;
}

void StaticCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	return;
}

void StaticCamera::ProcessMouseScroll(float yoffset)
{
	return;
}

void StaticCamera::UpdateCamera(glm::vec3 position)
{
}
