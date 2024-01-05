#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "Texture.hpp"
class Object 
{
private:
protected:
	virtual int getVAOSize() = 0;
	virtual float* getObjectVAO() = 0;
	unsigned int textureId;
	VAO vao;
	VBO vbo;
public:
	Object(glm::vec3 position, const char* path)
	{
		this->position = position;
		if(path != NULL)	textureId = Texture::loadTexture(path);
		vao.bindVAO();
		vbo.bindVBO();
	};

	virtual int getVertexSize() = 0;
	virtual void renderObject() = 0;
	
	glm::mat4 getModel()
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		float angle = 20.0f;
		return model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
	}

	glm::vec3 position;
	void bindVAO() { vao.bindVAO(); }
	void bindTexture(){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}
};