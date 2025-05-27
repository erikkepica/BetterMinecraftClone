#pragma once
#include"components/Component.h"

#include"components/Transform.h"
#include"components/Renderer.h"
#include"components/Material.h"

#include<string>

class GameObject
{
private:
	std::vector<std::unique_ptr<Component>> m_Components;
public:
	std::string name;

	GameObject()
	{
	}
	~GameObject()
	{
	}

	void GetComponent(typename component)
	{

	}

	void Generate(std::string name_)
	{
		name = name_;
		PushComponent(std::make_unique<Transform>());
	}

	void PushComponent(std::unique_ptr<Component> component)
	{
		m_Components.push_back(std::move(component));
	}
};