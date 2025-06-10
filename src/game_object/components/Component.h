#pragma once
#include"UIManager.h"

class Component
{
public:
	virtual void AddDebugToDrawArray(std::vector<std::unique_ptr<DebugDrawElement>>& win){}
	virtual std::string GetID() { return "NONE"; }
	virtual void Update();
	virtual void Start();
};