#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "SimpleObject.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include <vector>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main(void)
{

    GLFWwindow* window;


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);



    /* Make the window's context current */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader shader{ "vertex.glsl", "fragment.glsl" };

    std::vector<glm::vec3> positions{};


    positions.push_back(glm::vec3{ -0.5f, -0.5f, -0.5f });
    positions.push_back(glm::vec3{0.5f, -0.5f, -0.5f });
    positions.push_back(glm::vec3{0.5f, 0.5f, -0.5f });
    positions.push_back(glm::vec3{0.5f, 0.5f, -0.5f });
    positions.push_back(glm::vec3{-0.5f, 0.5f, -0.5f });
    positions.push_back(glm::vec3{-0.5f, -0.5f, -0.5f });

    positions.push_back(glm::vec3{ -0.5f, -0.5f, 0.5f});
    positions.push_back(glm::vec3{ 0.5f, -0.5f, 0.5f});
    positions.push_back(glm::vec3{ 0.5f, 0.5f, 0.5f});
    positions.push_back(glm::vec3{ 0.5f, 0.5f, 0.5f});
    positions.push_back(glm::vec3{ -0.5f, 0.5f, 0.5f});
    positions.push_back(glm::vec3{ -0.5f, -0.5f, 0.5f});

    positions.push_back(glm::vec3{-0.5f, 0.5f, 0.5f});
    positions.push_back(glm::vec3{-0.5f, 0.5f, -0.5f});
    positions.push_back(glm::vec3{-0.5f, -0.5f, -0.5f});
    positions.push_back(glm::vec3{-0.5f, -0.5f, -0.5f});
    positions.push_back(glm::vec3{-0.5f, -0.5f, 0.5f});
    positions.push_back(glm::vec3{-0.5f, 0.5f, 0.5f,});

    positions.push_back(glm::vec3{0.5f, 0.5f, 0.5f});
    positions.push_back(glm::vec3{0.5f, 0.5f, -0.5f});
    positions.push_back(glm::vec3{0.5f, -0.5f, -0.5f});
    positions.push_back(glm::vec3{0.5f, -0.5f, -0.5f});
    positions.push_back(glm::vec3{0.5f, -0.5f, 0.5f});
    positions.push_back(glm::vec3{0.5f, 0.5f, 0.5f});

    positions.push_back(glm::vec3{-0.5f, -0.5f, -0.5f});
    positions.push_back(glm::vec3{0.5f, -0.5f, -0.5f});
    positions.push_back(glm::vec3{0.5f, -0.5f, 0.5f});
    positions.push_back(glm::vec3{0.5f, -0.5f, 0.5f});
    positions.push_back(glm::vec3{-0.5f, -0.5f, 0.5f});
    positions.push_back(glm::vec3{-0.5f, -0.5f, -0.5f});

    positions.push_back(glm::vec3{-0.5f, 0.5f, -0.5f});
    positions.push_back(glm::vec3{ 0.5f, 0.5f, -0.5f });
    positions.push_back(glm::vec3{ 0.5f, 0.5f, 0.5f });
    positions.push_back(glm::vec3{ 0.5f, 0.5f, 0.5f });
    positions.push_back(glm::vec3{ -0.5f, 0.5f, 0.5f });
    positions.push_back(glm::vec3{ -0.5f, 0.5f, -0.5f });

    std::vector<glm::vec3> colors{};
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });

    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });

    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });

    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });

    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });

    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });

    std::vector<glm::vec2> textureCoordinates;
    textureCoordinates.push_back(glm::vec2{0.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 0.0f});

    textureCoordinates.push_back(glm::vec2{0.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 0.0f});

    textureCoordinates.push_back(glm::vec2{1.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 0.0f});

    textureCoordinates.push_back(glm::vec2{1.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 0.0f});

    textureCoordinates.push_back(glm::vec2{0.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{ 0.0f, 1.0f });

    textureCoordinates.push_back(glm::vec2{ 0.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{1.0f, 1.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{1.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 0.0f});
    textureCoordinates.push_back(glm::vec2{0.0f, 1.0f});


    SimpleObject object { positions, colors, textureCoordinates, glm::vec3{0.0f, 0.0f, 0.0f} };

    float* vertices = object.getObjectVAO();
    int n = sizeof(float) * object.getVAOSize();

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,  n, vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    shader.use();
    shader.setInt("texture1", 0);


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        // render the triangle
        shader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, object.position);
        float angle = 20.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader.setMat4("model", model); 

        glDrawArrays(GL_TRIANGLES, 0, object.getVertexSize());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    delete vertices;

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.ProcessMouseMovement(0, 2);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.ProcessMouseMovement(0, -2);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.ProcessMouseMovement(2, 0);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.ProcessMouseMovement(-2, 0);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}



// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}