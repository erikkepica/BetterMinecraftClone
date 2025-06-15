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
	std::shared_ptr<Transform> transform;
	std::string name;

	GameObject(const char* name_);
	GameObject();
	~GameObject()
	{
	}

	//returns first found component
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
	
	//returns all found components
	template<typename T>
	std::vector<std::shared_ptr<T>> GetComponents()
	{
		std::vector< std::shared_ptr<T>> foundComps{};

		for (auto& comp : m_Components)
		{
			if (comp->GetID() == T::ID())
				foundComps.push_back(std::dynamic_pointer_cast<T>(comp));
		}
		return foundComps;
	}
	void Generate(std::string name_);

	void PushComponent(std::shared_ptr<Component> component);

	void RenderUpdate();

	void AddDebugToWindow(DebugWindow& win);
};