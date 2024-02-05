#include "Window.hpp"
#include "FreeCamera.hpp"

GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

#define glCheckError() glCheckError_(__FILE__, __LINE__) 

void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}


float Window::lastX = 0.0f;
float Window::lastY = 0.0f;
int Window::cursorState = GLFW_CURSOR_DISABLED;
bool Window::spacePressed = false;
Engine* Window::engine = nullptr;

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    engine->camera->ProcessMouseScroll(static_cast<float>(yoffset));
} 

void Window::processInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) spacePressed = true;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && spacePressed)
    {
        cursorState = cursorState == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
        glfwSetInputMode(window, GLFW_CURSOR, cursorState);
        spacePressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        engine->camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        engine->camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        engine->camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        engine->camera->ProcessKeyboard(RIGHT, deltaTime);
}

void Window::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (cursorState == GLFW_CURSOR_NORMAL) return;
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    engine->camera->ProcessMouseMovement(xoffset, yoffset, true);
}

Window::Window(int width, int height) : cameraMode{FREE}, lightingModel{PHONG}, animate{false}, themeMode{DAY}, reflectorAngle{0.0f}
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "OpenGl scene", NULL, NULL);
    if (window == NULL)  throw("window error");

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) throw("Glad loader");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    lastX = width / 2.0f;
    lastY = height / 2.0f;

    engine = new Engine{ width, height };

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
}

Window Window::getInstance(int width, int height)
{
    return Window(width, height);
}

void Window::runWindow()
{
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glCheckError();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window, deltaTime);

        // render
        // ------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Options");
        ImGui::Text("Camera mode:");
        if (ImGui::RadioButton("Static", cameraMode == STATIC))             { engine->setCameraMode(STATIC);        cameraMode = STATIC; }
        if (ImGui::RadioButton("Free", cameraMode == FREE))                 { engine->setCameraMode(FREE);          cameraMode = FREE; }
        if (ImGui::RadioButton("Following", cameraMode == FOLLOWING))       { engine->setCameraMode(FOLLOWING);     cameraMode = FOLLOWING; }
        if (ImGui::RadioButton("Third person", cameraMode == THIRDPERSON))  { engine->setCameraMode(THIRDPERSON);   cameraMode = THIRDPERSON; }
        ImGui::Text("Lighting mode:");
        if (ImGui::RadioButton("Phong", lightingModel == PHONG))        { engine->setLightingModel(PHONG);      lightingModel = PHONG; }
        if (ImGui::RadioButton("Gourard", lightingModel == GOURARD))    { engine->setLightingModel(GOURARD);    lightingModel = GOURARD; }
        if (ImGui::RadioButton("Constant", lightingModel == CONSTANT))  { engine->setLightingModel(CONSTANT);   lightingModel = CONSTANT; }
        ImGui::Text("Theme:");
        if (ImGui::RadioButton("Day", themeMode == DAY))        { engine->setThemeMode(DAY); themeMode = DAY; }
        if (ImGui::RadioButton("Night", themeMode == NIGHT))    { engine->setThemeMode(NIGHT); themeMode = NIGHT; }
        ImGui::Checkbox("Animation", &animate);
        ImGui::SliderAngle("Set reflector angle", &reflectorAngle, -45.0f, 45.0f);
        ImGui::End();

        if (animate) { engine->animate(deltaTime); }
        engine->setReflectorAngle(reflectorAngle);
        engine->render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Window::~Window()
{
    delete engine;
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}
