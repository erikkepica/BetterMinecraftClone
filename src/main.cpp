#include<iostream>
#include <Windows.h>

#include<glad/glad.h>
#include <GLFW/glfw3.h>

#include"UIManager.h"

#include <glm/gtc/type_ptr.hpp>

#include"game_object/GameObject.h"

#include"Application/Application.h"

#include"Logging.h"

#include"game_object/Model.h"

#include"game_object/components/Camera.h"

#include"game_object/Scene.h"

void error_callback(int error, const char* description);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

glm::vec3 camPos(0.0f);
glm::vec3 camRot(0.0f); // pitch (x), yaw (y), roll (z)

float camSpeed = 5.0f;
float mouseSensitivity = 0.1f;

// Track time and mouse state
float lastX = 400, lastY = 300;
bool firstMouse = true;
void updateCamera(GLFWwindow* window, float deltaTime) {
	// Mouse movement
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (firstMouse) {
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)(xpos - lastX);
	float yoffset = (float)(lastY - ypos); // reversed Y

	lastX = (float)xpos;
	lastY = (float)ypos;

	camRot.y += xoffset * mouseSensitivity;
	camRot.x += yoffset * mouseSensitivity;

	// Clamp pitch
	if (camRot.x > 89.0f) camRot.x = 89.0f;
	if (camRot.x < -89.0f) camRot.x = -89.0f;

	// Calculate direction vectors
	glm::vec3 front;
	front.x = cos(glm::radians(camRot.y)) * cos(glm::radians(camRot.x));
	front.y = sin(glm::radians(camRot.x));
	front.z = sin(glm::radians(camRot.y)) * cos(glm::radians(camRot.x));
	front = glm::normalize(front);

	glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
	glm::vec3 up = glm::vec3(0,1,0);

	float velocity = camSpeed * deltaTime;

	// Movement keys
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camPos += front * velocity;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camPos -= front * velocity;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camPos -= right * velocity;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camPos += right * velocity;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camPos += up * velocity;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camPos -= up * velocity;
}


int main()
{
#ifdef _WIN32
#ifdef _MSC_VER 
#if PRODUCTION_BUILD == 0
	AllocConsole();
	(void)freopen("conin$", "r", stdin);
	(void)freopen("conout$", "w", stdout);
	(void)freopen("conout$", "w", stderr);
	std::cout.sync_with_stdio();
#endif
#endif
#endif
	
	LOG_INFO("This is an example for info logging!");
	LOG_WARNING("This is an example for warning logging!");
	LOG_ERROR("This is an example for error logging!", false);


	Application app({ "Game", {"Game", 800, 600}});
	app.window.SetKeyCallback(key_callback);

	
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Scene scene0;

	VertexBufferLayout attribs;
	attribs.Push<float>(3);
	attribs.Push<float>(2);
	attribs.Push<float>(3);
	attribs.Push<float>(3);
	attribs.Push<float>(3);


	Model model(attribs);
	model.LoadOBJ(RESOURCES_PATH "chicken/Chicken.obj");

	scene0.PushGameObject(std::make_shared<GameObject>("Chicken"));
	scene0.GetGameObject("Chicken")->PushComponent(std::make_shared<Renderer>(model));


	scene0.GetGameObject("Chicken")->PushComponent(std::make_shared<LitMaterial>(RESOURCES_PATH "vert.vert", RESOURCES_PATH "frag.frag", std::map<std::string, Texture>
	{
		{"diffuseSample",Texture(RESOURCES_PATH "chicken/textures/diffuse.png")},
		{"specularSample",Texture(RESOURCES_PATH "SpecularAll.png")},
		{"normalSampler",Texture(RESOURCES_PATH "chicken/textures/normal.png")},
	}));


	scene0.PushGameObject(std::make_shared<GameObject>("Camera"));
	scene0.GetGameObject("Camera")->PushComponent(std::make_shared<Camera>(scene0.GetGameObject("Camera")->transform, app.window.data));
	scene0.mainCamera = scene0.GetGameObject("Camera");





	DebugWindow enviromentWindow("Enviroment", ImGuiWindowFlags_None);
	scene0.enviroment.AddDebugToWindow(enviromentWindow);

	DebugWindow cameraInfo("Camera Info", ImGuiWindowFlags_None);
	cameraInfo.Push(std::make_unique<DragFloat3ElementInf>(&camPos[0], "Camera Position"));
	cameraInfo.Push(std::make_unique<DragFloat3ElementRange>(&camRot[0], "Camera Rotation", -360, 360));

	DebugWindow squareWindow("Game Object", ImGuiWindowFlags_None);
	DebugWindow cameraWindow("Camera", ImGuiWindowFlags_None);

	scene0.GetGameObject("Chicken")->AddDebugToWindow(squareWindow);
	scene0.GetGameObject("Camera")->AddDebugToWindow(cameraWindow);



	app.uiManager.Push(&enviromentWindow);
	app.uiManager.Push(&squareWindow);
	app.uiManager.Push(&cameraInfo);
	app.uiManager.Push(&cameraWindow);

	glfwSetInputMode(app.window.GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float lastTime = 0;

	bool fpsMode = true;
	bool togglePressed = false;


	while (!glfwWindowShouldClose(app.window.GetGLFWWindow()))
	{
		if (glfwGetKey(app.window.GetGLFWWindow(), GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS) {
			if (!togglePressed) {
				fpsMode = !fpsMode;
				glfwSetInputMode(app.window.GetGLFWWindow(), GLFW_CURSOR, fpsMode ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
				togglePressed = true;
			}
		}
		else {
			togglePressed = false;
		}

		float currentTime = (float)glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		glfwPollEvents();

		int width, height;

		glfwGetFramebufferSize(app.window.GetGLFWWindow(), &width, &height);
		if(fpsMode)
			updateCamera(app.window.GetGLFWWindow(), deltaTime);

		scene0.GetGameObject("Camera")->transform->position = camPos;
		scene0.GetGameObject("Camera")->transform->rotation = camRot;

		glViewport(0, 0, width, height);
		glClearColor(scene0.enviroment.bgColor[0], scene0.enviroment.bgColor[1], scene0.enviroment.bgColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene0.GetGameObject("Camera")->GetComponent<Camera>()->UpdateWindowData(app.window.data);

		scene0.Render();

		app.uiManager.Draw();

		glfwSwapBuffers(app.window.GetGLFWWindow());
	}
	app.Shutdown();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

