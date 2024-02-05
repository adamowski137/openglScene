#include "ThirdPersonCamera.hpp"

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Camera{ position, up, yaw, pitch }
{
}

ThirdPersonCamera::ThirdPersonCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: Camera{ posX, posY, posZ, upX, upY, upZ, yaw, pitch }
{
}

void ThirdPersonCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
}

void ThirdPersonCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
}

void ThirdPersonCamera::ProcessMouseScroll(float yoffset)
{
}

void ThirdPersonCamera::UpdateCamera(glm::vec3 position)
{
	Position = position + glm::vec3{0.0f, 0.4f, 0.0f};
}
