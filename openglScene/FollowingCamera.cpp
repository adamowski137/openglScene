#include "FollowingCamera.hpp"

FollowingCamera::FollowingCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Camera { position, up, yaw, pitch }
{
}

FollowingCamera::FollowingCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: Camera{ posX, posY, posZ, upX, upY, upZ, yaw, pitch }
{
}

void FollowingCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
}

void FollowingCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
}

void FollowingCamera::ProcessMouseScroll(float yoffset)
{
}

void FollowingCamera::UpdateCamera(glm::vec3 followPosition)
{
    glm::vec3 direction = glm::normalize(followPosition - Position);

    float yaw = glm::degrees(atan2(direction.z, direction.x));
    float pitch = glm::degrees(asin(direction.y));

    this->Yaw = yaw;
    this->Pitch = pitch;

    updateCameraVectors();
}
