#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Camera.hpp"
#include "Engine.hpp"

#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"



class Window
{
private:
    bool animate;
    float reflectorAngle;
    CameraMode cameraMode;
    LightingModel lightingModel;
    ThemeMode themeMode;
    GLFWwindow* window;
    static Engine* engine;
    static int cursorState;
    static bool spacePressed;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void processInput(GLFWwindow* window, float input);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    static float lastX;
    static float lastY;
  
    Window(int width, int height);
public:
    static Window getInstance(int width, int height);
    void runWindow();
    ~Window();
};

