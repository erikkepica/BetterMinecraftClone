#include"Scene.h"
#include <algorithm>
std::string Scene::GetName()
{
	return "Scene0";
}

void Scene::Render()
{
	for (auto o : m_GameObjects)
	{
		if (o->GetComponent<Renderer>() == nullptr)
		{
			continue;
		}
		o->GetComponent<LitMaterial>()->SetupMatricies(o->GetComponent<Transform>()->GetModel(), o->GetComponent<Transform>()->GetView(-mainCamera->transform->position, mainCamera->transform->rotation), mainCamera->GetComponent<Camera>()->GetProjection());
		o->GetComponent<LitMaterial>()->shader.SetFloat("time", glfwGetTime());
		o->GetComponent<LitMaterial>()->SetupLighting(enviroment.lightColor, enviroment.lightDir, enviroment.lightStrength, enviroment.ambientStrength, enviroment.ambientColor);
		o->GetComponent<LitMaterial>()->shader.SetVec3("viewPos", -mainCamera->transform->position);

		o->RenderUpdate();
	}
}

void Scene::PushGameObject(std::shared_ptr<GameObject> go)
{
	m_GameObjects.push_back(go);
}

std::shared_ptr<GameObject> Scene::GetGameObject(std::string name)
{
	auto it = std::find_if(m_GameObjects.begin(), m_GameObjects.end(), [&](const auto go)
	{
		return go->name == name;
	});
	if (it != m_GameObjects.end())
	{
		return *it;
	}
	else
	{
		LOG_WARNING((std::string("GetGameObject (By name) : Could not find a game object with name '") + name + std::string("' in scene '") + GetName() + "'").c_str());
		return nullptr;
	}
}

void SceneEnviromentSettings::AddDebugToWindow(DebugWindow& win)
{
	win.Push(std::make_unique<Color3Element>(bgColor, "Background Color"));
	win.Push(std::make_unique<Color3Element>(&lightColor[0], "Light Color"));
	win.Push(std::make_unique<Color3Element>(&ambientColor[0], "Ambient Color"));
	win.Push(std::make_unique<DragFloat3ElementInf>(&lightDir[0], "Light Dir"));
	win.Push(std::make_unique<DragFloat1ElementInf>(&lightStrength, "Light Strength"));
	win.Push(std::make_unique<DragFloat1ElementInf>(&ambientStrength, "Ambient Strength"));
}
