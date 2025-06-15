#include"Scene.h"

std::string Scene::GetName()
{
	return "Default";
}

void Scene::Render()
{
	for (auto o : m_GameObjects)
	{
/*		o.GetComponent<LitMaterial>()->SetupMatricies(cube.GetComponent<Transform>()->GetModel(), cube.GetComponent<Transform>()->GetView(-camPos, camRot), projection);
		o.GetComponent<LitMaterial>()->shader.SetFloat("time", glfwGetTime());
		o.GetComponent<LitMaterial>()->SetupLighting(lightColor, lightDir, lightStrength, ambientStrength, ambientColor);
		o.GetComponent<LitMaterial>()->shader.SetVec3("viewPos", -camPos);
*/
		o.RenderUpdate();
	}
}