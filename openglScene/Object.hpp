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
	Object(glm::vec3 position, const char* path) {
		this->position = position;
		textureId = Texture::loadTexture(path);
		vao.bindVAO();
		vbo.bindVBO();
	};

	virtual int getVertexSize() = 0;
	
	glm::vec3 position;
	void renderObject(Shader& shader) {
		vao.bindVAO();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		float angle = 20.0f;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, getVertexSize());
	};
	void bindVAO() { vao.bindVAO(); }
	void bindTexture(){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}
};