#include "Application.h"
#include<glad/glad.h>

void error_callback(int error, const char* description)
{
	LOG_ERROR("GLFW: " << error << ", " << description, false);
}

Application::Application(ApplicationData data)
	:name(data.name), window({ data.windowData }),uiManager()
{
	InitGLFW();
	window.Create();
	InitGLAD();
	uiManager.Init(window.GetGLFWWindow());
}

Application::~Application()
{
	glfwTerminate();
}

void Application::InitGLFW()
{

	if (!glfwInit())
	{
		LOG_ERROR("GLFW: Failed to initialize", true);
	}
	LOG_INFO("GLFW: Initialized");
	glfwSetErrorCallback(error_callback);
}

void Application::InitGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("GLAD: Failed to initialize", true);
	}
	LOG_INFO("GLAD: Initialized");
}

void Application::Shutdown()
{
	uiManager.Shutdown();
	window.Shutdown();
	glfwTerminate();
}

void Application::Run()
{
}