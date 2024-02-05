#include "FreeCamera.hpp"

FreeCamera::FreeCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Camera{ position, up, yaw, pitch }
{
}
FreeCamera::FreeCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Camera{posX, posY, posZ, upX, upY, upZ, yaw, pitch}
{
}

void FreeCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void FreeCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
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

void FreeCamera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void FreeCamera::UpdateCamera(glm::vec3 position)
{
}
