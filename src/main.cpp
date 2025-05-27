#include<iostream>
#include <Windows.h>

#include<glad/glad.h>
#include <GLFW/glfw3.h>

#include"UIManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"game_object/GameObject.h"

#include"Logging.h"

void error_callback(int error, const char* description);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);



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

	if (!glfwInit())
	{
		LOG_ERROR("GLFW: Failed to initialize", true);
	}
	LOG_INFO("GLFW: Initialized");
	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (!window)
	{
		LOG_ERROR("GLFW: Window failed to create", true);
	}
	LOG_INFO("GLFW: Window opened");

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("GLAD: Failed to initialize", true);
	}
	LOG_INFO("GLAD: Initialized");
	
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_DEPTH_TEST);



	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices_[] = {
		// Front face (+Z)
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

	   -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,

		// Back face (-Z)
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,

	   -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

		// Left face (-X)
	   -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

	   // Right face (+X)
	   0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	   0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	   0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

	   0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	   0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	   0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,

	   // Top face (+Y)
	  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	  -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	   0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,

	   0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	   0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,

	  // Bottom face (-Y)
	 -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	  0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,

	  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	 -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	 -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  0.0f, -1.0f, 0.0f
	};
	int vSize = sizeof(vertices_) / sizeof(vertices_[0]);
	unsigned int indices_[] = {
		0, 1, 2,  3, 4, 5,      // front
		6, 7, 8,  9,10,11,      // back
	   12,13,14, 15,16,17,      // left
	   18,19,20, 21,22,23,      // right
	   24,25,26, 27,28,29,      // top
	   30,31,32, 33,34,35       // bottom
	};
	int iSize = sizeof(indices_) / sizeof(indices_[0]);

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	vertices.assign(vertices_, vertices_+vSize);
	indices.assign(indices_, indices_+iSize);

	VertexBufferLayout attribs;
	attribs.Push<float>(3);
	attribs.Push<float>(2);
	attribs.Push<float>(3);


	Renderer testObj(vertices, indices, attribs);
	LitMaterial mat(RESOURCES_PATH "vert.vert", RESOURCES_PATH "frag.frag", std::vector<const char*>
	{
		RESOURCES_PATH "Aki.png"
	});

	float bgColor[]{.7,1,1};
	glm::vec3 lightColor(1, 1, 1);
	glm::vec3 lightDir(1, -1, -1);
	float ambientStrength = 0.7f;
	float lightStrength = 0.6f;

	glm::vec4 squareColor(1,1,1,1);
	bool squareSpin = false;

	Transform squareTransform;



	UIManager uiManager;
	uiManager.Init(window);


	DebugWindow enviromentWindow("Enviroment", ImGuiWindowFlags_None);
	enviromentWindow.Push(std::make_unique<Color3Element>(bgColor, "Background Color"));
	enviromentWindow.Push(std::make_unique<Color3Element>(&lightColor[0], "Light Color"));
	enviromentWindow.Push(std::make_unique<DragFloat3ElementInf>(&lightDir[0], "Light Dir"));
	enviromentWindow.Push(std::make_unique<DragFloat1ElementInf>(&lightStrength, "Light Strength"));
	enviromentWindow.Push(std::make_unique<DragFloat1ElementInf>(&ambientStrength, "Ambient Strength"));


	DebugWindow squareWindow("Square", ImGuiWindowFlags_None);
	squareWindow.Push(std::make_unique<Color3Element>(&squareColor[0], "Color"));
	squareWindow.Push(std::make_unique<BoolElement>(&squareSpin, "Spin"));
	squareTransform.AddDebugToWindow(squareWindow);
	mat.AddDebugToWindow(squareWindow);



	uiManager.Push(&enviromentWindow);
	uiManager.Push(&squareWindow);


	bool enable = true;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		if(squareSpin)
			squareTransform.rotation.y = 360*sin(glfwGetTime());


		glm::mat4 model(1);
		model = glm::rotate(model, glm::radians(squareTransform.rotation.x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(squareTransform.rotation.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(squareTransform.rotation.z), glm::vec3(0, 0, 1));
		model = glm::scale(model, squareTransform.scale);

		glm::mat4 view(1);
		view = glm::translate(view, squareTransform.position);

		glm::mat4 projection(1);
		projection = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.01f, 100.0f);

		glViewport(0, 0, width, height);
		glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat.model = model;
		mat.view = view;
		mat.projection = projection;
		mat.color = squareColor;
		mat.lightColor = lightColor;
		mat.lightPos = lightDir;
		mat.ambientStrength = ambientStrength;
		mat.lightStrength = lightStrength;

		mat.Use();
		testObj.Draw();

		uiManager.Draw();

		glfwSwapBuffers(window);
	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void error_callback(int error, const char* description)
{
	LOG_ERROR("GLFW: " << error << ", " << description, false);
}