#pragma once
#include<vector>
#include"GameObject.h"
#include"components/Camera.h"
#include<memory>

class SceneEnviromentSettings
{
public:
	float bgColor[3] = {.3,.5,1};
	glm::vec3 lightColor = glm::vec3(1, 1, 1);
	glm::vec3 ambientColor = glm::vec3(1, 1, 1);
	glm::vec3 lightDir = glm::vec3(1, -1, -1);
	float ambientStrength = 0.37f;
	float lightStrength = 1.0f;

	void AddDebugToWindow(DebugWindow& win);
};

class Scene
{
public:
	SceneEnviromentSettings enviroment;
	
	std::shared_ptr<GameObject> mainCamera;
	virtual std::string GetName();
	virtual void Render();

	void PushGameObject(std::shared_ptr<GameObject> go);
	
	std::shared_ptr<GameObject> GetGameObject(std::string name);

private:
	std::vector<std::shared_ptr<GameObject>> m_GameObjects;
};
