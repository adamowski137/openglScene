#include "Engine.hpp"
#include "Utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Engine::Engine(int width, int height) : simpleObjectShader{ Shader{"simple_vertex.glsl", NULL, NULL, "simple_fragment.glsl"} }, 
	smoothObjectShader{ Shader{"smooth_vertex.glsl", "smooth_tcs.glsl", "smooth_tes.glsl", "smooth_fragment.glsl"} }, 
	lightObjectShader{ Shader{"light_vertex.glsl", NULL, NULL, "light_fragment.glsl"} },
	width{width}, height{height},
	scene{}
{
	setOneTimeShaderData();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPatchParameteri(GL_PATCH_VERTICES, 16);
}

Engine::~Engine()
{
}

void Engine::render(glm::mat4 view, glm::vec3 position)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto smoothObjects = scene.getSmoothObjects();
	auto simpleObjects = scene.getSimpleObjects();
	auto lightObjects = scene.getLightSources();
	// smooth objects
	smoothObjectShader.use();
	for (auto& object : smoothObjects)
	{
		object->bindTexture();
		glm::mat4 model = object->getModel();
		smoothObjectShader.setMat4("view", view);
		smoothObjectShader.setMat4("model", model);
		smoothObjectShader.setVec3("cameraPos", position);
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
		simpleObjectShader.setVec3("cameraPos", position);
		object->renderObject();
	}

	lightObjectShader.use();
	for (auto& object : lightObjects)
	{
		glm::mat4 model = object->getModel();
		lightObjectShader.setMat4("view", view);
		lightObjectShader.setMat4("model", model);
		lightObjectShader.setVec3("lightColor", object->getLightArguments().color);
		object->renderObject();
	}
}

void Engine::setOneTimeShaderData()
{
	glm::mat4 projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
	auto lightSources = scene.getLightSources();

	// smooth object setup
	smoothObjectShader.use();
	smoothObjectShader.setInt("texture1", 0);
    smoothObjectShader.setFloat("detail", 256);
	smoothObjectShader.setMat4("projection", projection);
	setLightData(lightSources, smoothObjectShader);

	// simple object setup

	simpleObjectShader.use();
	simpleObjectShader.setInt("texture1", 0);
	simpleObjectShader.setMat4("projection", projection);
	setLightData(lightSources, simpleObjectShader);
	
	lightObjectShader.use();
	lightObjectShader.setMat4("projection", projection);

}

void Engine::setLightData(std::vector<LightSource*> lights, const Shader& shader)
{
	int n = lights.size();
	shader.setInt("lightAmount", n);
	for (int i = 0; i < n; i++)
	{
		std::stringstream s;
		std::string location;
		LightArguments args = lights[i]->getLightArguments();
		s << "lightArgs[" << i << "]";
		location = s.str();
		shader.setFloat(location + ".strength", args.strength);
		shader.setVec3(location + ".position", args.position);
		shader.setVec3(location + ".color", args.color);
	}
}


