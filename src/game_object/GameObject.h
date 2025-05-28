#pragma once
#include"components/Component.h"

#include"components/Transform.h"
#include"components/Renderer.h"
#include"components/Material.h"

#include<string>

class GameObject
{
private:
	std::vector<std::shared_ptr<Component>> m_Components;
public:
	std::string name;

	GameObject(const char* name_)
	{
		Generate(name_);
	}
	GameObject()
	{
		Generate("GameObject");
	}
	~GameObject()
	{
	}

	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		for (auto& comp : m_Components)
		{
			if (comp->GetID() == T::ID())
				return std::dynamic_pointer_cast<T>(comp);
		}
		return nullptr;
	}

	void Generate(std::string name_)
	{
		name = name_;
		PushComponent(std::make_shared<Transform>());
	}

	void PushComponent(std::shared_ptr<Component> component)
	{
		m_Components.push_back(component);
	}

	void RenderUpdate()
	{
		GetComponent<LitMaterial>()->Use();
		GetComponent<Renderer>()->Draw();
	}

	void AddDebugToWindow(DebugWindow& win)
	{
		for (int i = 0; i < m_Components.size(); i++)
		{
			std::vector<std::unique_ptr<DebugDrawElement>> elems{};
			m_Components[i]->AddDebugToDrawArray(elems);
			std::unique_ptr<HeaderElement> header = std::make_unique<HeaderElement>(nullptr, m_Components[i]->GetID(), elems);
			win.Push(std::move(header));
		}
	}
};