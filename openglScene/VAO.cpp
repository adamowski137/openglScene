#include "VAO.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &ID);
}

void VAO::bindVAO()
{
	glBindVertexArray(ID);
}

void VAO::bufferData(int vaoSize, void* vertices, GLenum usage)
{
	glBufferData(GL_ARRAY_BUFFER, vaoSize, vertices, usage);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}
