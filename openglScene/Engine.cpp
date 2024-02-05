#include "Engine.hpp"
#include "Utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const glm::vec3 Engine::ThemeColors[2] = {glm::vec3{0.2f, 0.2f, 1.0f}, glm::vec3{0.0f, 0.0f, 0.5f}};
const glm::vec3 Engine::ThemeLightColors[2] = { glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{1.0f, 1.0f, 0.0f} };

Engine::Engine(int width, int height) : simpleObjectShader{ "simple_vertex.glsl", NULL, NULL, "simple_fragment.glsl" },  
	lightObjectShader{ "light_vertex.glsl", NULL, NULL, "light_fragment.glsl" },
	modelObjectShader{ "model_vertex.glsl", NULL, NULL, "model_fragment.glsl" },
	width{ width }, height{ height }, scene{}, freeCamera{ glm::vec3(0.0f, 0.0f, 3.0f) }, staticCamera{ glm::vec3(3.0f, 10.0f, 5.0f), glm::vec3{0.0f, 1.0f, 0.0f }, 0.0f, -89.0f },
	followingCamera{ glm::vec3(0.0f, 7.0f, 0.0f), }, camera{&freeCamera}
{
	setOneTimeShaderData();
	glm::vec3 color = ThemeColors[DAY];
	glClearColor(color.r, color.g, color.b, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

Engine::~Engine()
{
}

void Engine::setReflectorData()
{
	Model* object = scene.specialObject;
	scene.specialObjectReflectorLeft.position = object->position;
	scene.specialObjectReflectorRight.position = object->position;
	glm::mat4 model = object->getModel();

	glm::vec3 leftOffset = glm::vec4(-0.5f, 0.0f, 0.0f, 1.0f) * model;
	glm::vec3 rightOffset = glm::vec4(0.5f, 0.0f, 0.0f, 1.0f) * model;

	auto left = scene.specialObjectReflectorLeft;
	auto right = scene.specialObjectReflectorRight;

	modelObjectShader.use();
	modelObjectShader.setVec3("leftReflector.position", left.position + leftOffset);
	modelObjectShader.setVec3("rightReflector.position", right.position + rightOffset);
	modelObjectShader.setVec3("leftReflector.direction", left.direction);
	modelObjectShader.setVec3("rightReflector.direction", right.direction);	

}

void Engine::animate(float dt)
{
	auto objects = scene.getSmoothObjects();
	for (auto& o : objects)
	{
		o->animate(dt);
	}
	scene.specialObject->animate(dt);
}

void Engine::render()
{
	glm::mat4 view = camera->GetViewMatrix();
	glm::vec3 position = camera->Position;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setReflectorData();


	auto smoothObjects = scene.getSmoothObjects();
	auto lightObjects = scene.getLightSources();
	auto models = scene.getModels();
	// smooth objects
	simpleObjectShader.use();
	simpleObjectShader.setVec3("cameraPos", position);
	simpleObjectShader.setMat4("view", view);
	for (auto& object : smoothObjects)
	{
		glm::mat4 model = object->getModel();
		simpleObjectShader.setMat4("model", model);
		object->renderObject();
	}

	modelObjectShader.use();
	modelObjectShader.setVec3("cameraPos", position);
	modelObjectShader.setMat4("view", view);
	for (auto& object : models)
	{
		glm::mat4 model = object->getModel();
		modelObjectShader.setMat4("model", model);
		object->renderObject(modelObjectShader);
	}
	modelObjectShader.setMat4("model", scene.specialObject->getModel());
	scene.specialObject->renderObject(modelObjectShader);

	lightObjectShader.use();
	lightObjectShader.setMat4("view", view);
	lightObjectShader.setVec3("cameraPos", position);

	for (auto& object : lightObjects)
	{
		glm::mat4 model = object->getModel();
		lightObjectShader.setMat4("model", model);
		lightObjectShader.setVec3("lightColor", object->getLightArguments().color);
		object->renderObject();
	}
		
	camera->UpdateCamera(scene.specialObject->position);
}

void Engine::setCameraMode(CameraMode mode)
{
	if (mode == FREE)			camera = &freeCamera;
	if (mode == STATIC)			camera = &staticCamera;
	if (mode == FOLLOWING)		camera = &followingCamera;
	if (mode == THIRDPERSON)	camera = &thirdPersonCamera;
}

void Engine::setLightingModel(LightingModel model) 
{
	simpleObjectShader.use();
	simpleObjectShader.setInt("lightingModel", model);
	modelObjectShader.use();
	modelObjectShader.setInt("lightingModel", model);
}

void Engine::setThemeMode(ThemeMode themeMode)
{
	glm::vec3 color = ThemeColors[themeMode];
	glClearColor(color.r, color.g, color.b, 1.0f);
	modelObjectShader.use();
	modelObjectShader.setVec3("theme", color);
	lightObjectShader.use();
	lightObjectShader.setVec3("theme", color);
	simpleObjectShader.use();
	simpleObjectShader.setVec3("theme", color);
	scene.setLightColor(ThemeLightColors[themeMode]);
	scene.getLightSources();
	setLightData(scene.getLightSources(), modelObjectShader);
	setLightData(scene.getLightSources(), simpleObjectShader);
	lightObjectShader.use();
	lightObjectShader.setVec3("lightColor", ThemeLightColors[themeMode]);
}

void Engine::setReflectorAngle(float angle)
{
	glm::vec3 direction = scene.specialObject->direction;
	glm::vec3 position = scene.specialObject->position;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	float newX = direction.x * cosAngle - direction.z * sinAngle;
	float newZ = direction.x * sinAngle + direction.z * cosAngle;
	scene.specialObjectReflectorLeft.direction = -glm::vec3(newX, direction.y, newZ);;
	scene.specialObjectReflectorRight.direction = -glm::vec3(newX, direction.y, newZ);
	scene.specialObjectReflectorLeft.position = position;
	scene.specialObjectReflectorRight.position = position;
}


void Engine::setOneTimeShaderData()
{
	auto left = scene.specialObjectReflectorLeft;
	auto right = scene.specialObjectReflectorRight;
	glm::mat4 projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
	auto lightSources = scene.getLightSources();

	// simple object setup

	simpleObjectShader.use();
	simpleObjectShader.setMat4("projection", projection);
	setLightData(lightSources, simpleObjectShader);
	
	modelObjectShader.use();
	modelObjectShader.setMat4("projection", projection);
	modelObjectShader.setVec3("leftReflector.color", left.color);
	modelObjectShader.setVec3("rightReflector.color", right.color);
	modelObjectShader.setFloat("leftReflector.cutOff", left.cutOff);
	modelObjectShader.setFloat("rightReflector.cutOff", right.cutOff);
	setLightData(lightSources, modelObjectShader);

	lightObjectShader.use();
	lightObjectShader.setMat4("projection", projection);

	setLightingModel(PHONG);
	setThemeMode(DAY);
}

void Engine::setLightData(std::vector<LightSource*> lights, const Shader& shader)
{
	int n = lights.size();
	shader.use();
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


