#include "EBO.hpp"
#include <glad/glad.h>

EBO::EBO()
{
	glGenBuffers(1, &ID);
}

EBO::~EBO()
{
	glDeleteBuffers(1, &ID);
}

void EBO::bindEBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
