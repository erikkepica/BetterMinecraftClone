#include"GameObject.h"

GameObject::GameObject(const char* name_)
{
	Generate(name_);
}

GameObject::GameObject()
{
	Generate("GameObject");
}

void GameObject::Generate(std::string name_)
{
	name = name_;
	transform = std::make_shared<Transform>();
	PushComponent(transform);
}

void GameObject::PushComponent(std::shared_ptr<Component> component)
{
	m_Components.push_back(component);
}

void GameObject::RenderUpdate()
{
	GetComponent<LitMaterial>()->Use();
	GetComponent<Renderer>()->Draw();
}

void GameObject::AddDebugToWindow(DebugWindow& win)
{
	for (int i = 0; i < m_Components.size(); i++)
	{
		std::vector<std::unique_ptr<DebugDrawElement>> elems{};
		m_Components[i]->AddDebugToDrawArray(elems);
		std::unique_ptr<HeaderElement> header = std::make_unique<HeaderElement>(nullptr, m_Components[i]->GetID(), elems);
		win.Push(std::move(header));
	}
}
