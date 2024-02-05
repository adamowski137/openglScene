#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "Camera.hpp"

class FreeCamera : public Camera
{
public:

    FreeCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    FreeCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    void ProcessKeyboard(Camera_Movement direction, float deltaTime) override;
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) override;
    void ProcessMouseScroll(float yoffset) override;
    void UpdateCamera(glm::vec3 position) override;
private:
};
