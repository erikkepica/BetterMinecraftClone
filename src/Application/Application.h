#pragma once
#include"Window.h"
#include<memory>
#include<string>
#include "DataStructs.h"	
#include"UIManager.h"

class Application
{
public:
	std::string name;
	Window window;
	UIManager uiManager;

	Application(ApplicationData data);
	~Application();

	void InitGLFW();
	void InitGLAD();

	void Shutdown();

	void Run();
private:
};