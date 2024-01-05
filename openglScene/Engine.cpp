#include "Engine.hpp"
#include "Utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Engine::Engine(int width, int height) : simpleObjectShader{ Shader{"simple_vertex.glsl", NULL, NULL, "simple_fragment.glsl"} }, 
	smoothObjectShader{ Shader{"smooth_vertex.glsl", "smooth_tcs.glsl", "smooth_tes.glsl", "smooth_fragment.glsl"} }, width{width}, height{height}
{
	setOneTimeShaderData();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPatchParameteri(GL_PATCH_VERTICES, 16);
	loadModels();
}

Engine::~Engine()
{
	for (auto& object : smoothObjects)
	{
		delete object;
	}
	for (auto& object : simpleObjects)
	{
		delete object;
	}
}

void Engine::render(glm::mat4 view)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// smooth objects
	smoothObjectShader.use();
	for (auto& object : smoothObjects)
	{
		object->bindTexture();
		glm::mat4 model = object->getModel();
		smoothObjectShader.setMat4("view", view);
		smoothObjectShader.setMat4("model", model);
		glPatchParameteri(GL_PATCH_VERTICES, 16);
		glDisable(GL_CULL_FACE);
		object->renderObject();
	}

	//simple objects
	simpleObjectShader.use();
	for (auto& object : simpleObjects)
	{
		object->bindTexture();
		glm::mat4 model = object->getModel();
		simpleObjectShader.setMat4("view", view);
		simpleObjectShader.setMat4("model", model);
		object->renderObject();
	}
}

void Engine::loadModels()
{
	smoothObjects.push_back(Utils::generateBezier(glm::vec3(0.0f, 0.0f, 0.0f), "wall.jpg", 4));
	simpleObjects.push_back(Utils::generateBox(glm::vec3(1.0f, 2.0f, 0.0f), "wall.jpg"));
}

void Engine::setOneTimeShaderData()
{
	glm::mat4 projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

	// smooth object setup
	smoothObjectShader.use();
	smoothObjectShader.setInt("texture1", 0);
	smoothObjectShader.setVec3("tint", glm::vec3{ 0.5f, 0.5f, 0.5f });
    smoothObjectShader.setFloat("detail", 256);
	smoothObjectShader.setMat4("projection", projection);

	// simple object setup

	simpleObjectShader.use();
	simpleObjectShader.setInt("texture1", 0);
	simpleObjectShader.setMat4("projection", projection);
}


