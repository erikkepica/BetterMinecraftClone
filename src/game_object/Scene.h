#pragma once
#include<vector>
#include"GameObject.h"

class Scene
{
public:
	virtual std::string GetName();
	virtual void Render();
private:
	std::vector<GameObject> m_GameObjects;
};
