#pragma once
#include<string>
#include<GLFW/glfw3.h>
#include"Logging.h"
#include"DataStructs.h"

class Window
{
public:
	WindowData data;

	Window(WindowData data);
	~Window();

	void Create();
	void SetKeyCallback(void (*KeyCallback)(GLFWwindow*, int, int, int, int));
	void Bind();
	GLFWwindow* GetGLFWWindow();

	void Shutdown();
private:
	GLFWwindow* m_Window;
};