#pragma once
#include <vector>
#include "SmoothObject.hpp"
#include "SimpleObject.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "FreeCamera.hpp"
#include "StaticCamera.hpp"
#include "FollowingCamera.hpp"
#include "ThirdPersonCamera.hpp"
#include "State.hpp"

class Engine 
{
private:
	int width;
	int height;
	Scene scene;
	FreeCamera freeCamera;
	StaticCamera staticCamera;
	FollowingCamera followingCamera;
	ThirdPersonCamera thirdPersonCamera;

	const Shader simpleObjectShader;
	const Shader modelObjectShader;
	const Shader lightObjectShader;

	const static glm::vec3 ThemeColors[2];
	const static glm::vec3 ThemeLightColors[2];


	void setOneTimeShaderData();
	void setLightData(std::vector<LightSource*> lights, const Shader& shader);
	void setReflectorData();
public:

	Engine(int width, int height);
	~Engine();
	Camera* camera;

	void animate(float dt);
	void render();
	void setCameraMode(CameraMode mode);
	void setLightingModel(LightingModel model);
	void setThemeMode(ThemeMode themeMode);
	void setReflectorAngle(float angle);
};