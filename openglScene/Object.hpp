#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
class Object 
{
private:
protected:
	virtual int getVAOSize() = 0;
	virtual float* getObjectVAO() = 0;
	VAO vao;
	VBO vbo;
public:
	Object(glm::vec3 position, const char* path)
	{
		this->position = position;
		vao.bindVAO();
		vbo.bindVBO();
	};

	virtual int getVertexSize() = 0;
	virtual void renderObject() = 0;
	
	virtual glm::mat4 getModel()
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		return model;
	}

	glm::vec3 position;
	void bindVAO() { vao.bindVAO(); }
};