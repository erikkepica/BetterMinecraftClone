#include<iostream>
#include <Windows.h>

#include<glad/glad.h>
#include <GLFW/glfw3.h>

#include"UIManager.h"

#include <glm/gtc/type_ptr.hpp>

#include"game_object/GameObject.h"

#include"Application/Application.h"

#include"Logging.h"

void error_callback(int error, const char* description);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);



/*
TODO:

	- Abstracting window and application logic away
	- Making the game engine a library
*/
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
	vertices.assign(vertices_, vertices_ + vSize);
	indices.assign(indices_, indices_ + iSize);


	const unsigned int X_SEGMENTS = 64;
	const unsigned int Y_SEGMENTS = 64;
	float M_PI = 3.14f;
	std::vector<unsigned int> sphereIndices;

	struct Vertex {
		glm::vec3 position;
		glm::vec2 texCoord;
		glm::vec3 normal;
		glm::vec3 tangent = glm::vec3(0.0f);
		glm::vec3 bitangent = glm::vec3(0.0f);
	};

	std::vector<Vertex> vertexData((X_SEGMENTS + 1) * (Y_SEGMENTS + 1));

	// Vertex generation
	for (unsigned int y = 0; y <= Y_SEGMENTS; ++y) {
		for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
			float xSegment = (float)x / X_SEGMENTS;
			float ySegment = (float)y / Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
			float yPos = std::cos(ySegment * M_PI);
			float zPos = std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);

			Vertex& v = vertexData[y * (X_SEGMENTS + 1) + x];
			v.position = glm::vec3(xPos, yPos, zPos);
			v.texCoord = glm::vec2(1-xSegment, 1-ySegment);
			v.normal = glm::normalize(glm::vec3(xPos, yPos, zPos));
		}
	}

	// Index and tangent/bitangent generation
	for (unsigned int y = 0; y < Y_SEGMENTS; ++y) {
		for (unsigned int x = 0; x < X_SEGMENTS; ++x) {
			int i0 = y * (X_SEGMENTS + 1) + x;
			int i1 = (y + 1) * (X_SEGMENTS + 1) + x;
			int i2 = i0 + 1;
			int i3 = i1 + 1;

			auto calcTangentBitangent = [&](int a, int b, int c) {
				const glm::vec3& pos1 = vertexData[a].position;
				const glm::vec3& pos2 = vertexData[b].position;
				const glm::vec3& pos3 = vertexData[c].position;

				const glm::vec2& uv1 = vertexData[a].texCoord;
				const glm::vec2& uv2 = vertexData[b].texCoord;
				const glm::vec2& uv3 = vertexData[c].texCoord;

				glm::vec3 edge1 = pos2 - pos1;
				glm::vec3 edge2 = pos3 - pos1;

				glm::vec2 deltaUV1 = uv2 - uv1;
				glm::vec2 deltaUV2 = uv3 - uv1;

				float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

				glm::vec3 tangent = f * (deltaUV2.y * edge1 - deltaUV1.y * edge2);
				glm::vec3 bitangent = f * (-deltaUV2.x * edge1 + deltaUV1.x * edge2);

				vertexData[a].tangent += tangent;
				vertexData[b].tangent += tangent;
				vertexData[c].tangent += tangent;

				vertexData[a].bitangent += bitangent;
				vertexData[b].bitangent += bitangent;
				vertexData[c].bitangent += bitangent;
				};

			// Two triangles per quad
			sphereIndices.push_back(i0); sphereIndices.push_back(i1); sphereIndices.push_back(i2);
			calcTangentBitangent(i0, i1, i2);

			sphereIndices.push_back(i2); sphereIndices.push_back(i1); sphereIndices.push_back(i3);
			calcTangentBitangent(i2, i1, i3);
		}
	}

	// Normalize tangents and bitangents
	for (auto& v : vertexData) {
		v.tangent = glm::normalize(v.tangent);
		v.bitangent = glm::normalize(v.bitangent);
	}

	std::vector<float> sphereVertices;
	for (const auto& v : vertexData) {
		sphereVertices.insert(sphereVertices.end(), {
			v.position.x, v.position.y, v.position.z,
			v.texCoord.x, v.texCoord.y,
			v.normal.x, v.normal.y, v.normal.z,
			v.tangent.x, v.tangent.y, v.tangent.z,
			v.bitangent.x, v.bitangent.y, v.bitangent.z
			});
	}

	bool oddRow = false;
	for (unsigned int y = 0; y < Y_SEGMENTS; ++y) {
		for (unsigned int x = 0; x < X_SEGMENTS; ++x) {
			unsigned int i0 = y * (X_SEGMENTS + 1) + x;
			unsigned int i1 = (y + 1) * (X_SEGMENTS + 1) + x;

			sphereIndices.push_back(i0);
			sphereIndices.push_back(i1);
			sphereIndices.push_back(i0 + 1);

			sphereIndices.push_back(i0 + 1);
			sphereIndices.push_back(i1);
			sphereIndices.push_back(i1 + 1);
		}
	}


	VertexBufferLayout attribs;
	attribs.Push<float>(3);
	attribs.Push<float>(2);
	attribs.Push<float>(3);
	attribs.Push<float>(3);
	attribs.Push<float>(3);


	GameObject cube;
	Renderer renderer;
	cube.PushComponent(std::make_shared<Renderer>(sphereVertices, sphereIndices, attribs));


	cube.PushComponent(std::make_shared<LitMaterial>(RESOURCES_PATH "vert.vert", RESOURCES_PATH "frag.frag", std::map<std::string, Texture>
	{
		{"earth",Texture(RESOURCES_PATH "Earth.png")},
		{"earthSpecular",Texture(RESOURCES_PATH "EarthSpecular.png")},
		{"normalMapSampler",Texture(RESOURCES_PATH "EarthNormal.png")},
		{"noise",Texture(RESOURCES_PATH "Clouds.png")}
	}));



	float bgColor[]{0,0,0};
	glm::vec3 lightColor(1, 1, 1);
	glm::vec3 lightDir(1, -1, -1);
	float ambientStrength = 0.07f;
	float lightStrength = 3.0f;


	DebugWindow enviromentWindow("Enviroment", ImGuiWindowFlags_None);
	enviromentWindow.Push(std::make_unique<Color3Element>(bgColor, "Background Color"));
	enviromentWindow.Push(std::make_unique<Color3Element>(&lightColor[0], "Light Color"));
	enviromentWindow.Push(std::make_unique<DragFloat3ElementInf>(&lightDir[0], "Light Dir"));
	enviromentWindow.Push(std::make_unique<DragFloat1ElementInf>(&lightStrength, "Light Strength"));
	enviromentWindow.Push(std::make_unique<DragFloat1ElementInf>(&ambientStrength, "Ambient Strength"));

	DebugWindow cameraInfo("Camera Info", ImGuiWindowFlags_None);
	cameraInfo.Push(std::make_unique<DragFloat3ElementInf>(&camPos[0], "Camera Position"));
	cameraInfo.Push(std::make_unique<DragFloat3ElementRange>(&camRot[0], "Camera Rotation", -360, 360));

	DebugWindow squareWindow("Game Object", ImGuiWindowFlags_None);

	cube.AddDebugToWindow(squareWindow);



	app.uiManager.Push(&enviromentWindow);
	app.uiManager.Push(&squareWindow);
	app.uiManager.Push(&cameraInfo);

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

		glm::mat4 projection(1);
		projection = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.01f, 3000.0f);

		glViewport(0, 0, width, height);
		glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cube.GetComponent<LitMaterial>()->SetupMatricies(cube.GetComponent<Transform>()->GetModel(), cube.GetComponent<Transform>()->GetView(-camPos,camRot), projection);
		cube.GetComponent<LitMaterial>()->shader.SetFloat("time", glfwGetTime());
		cube.GetComponent<LitMaterial>()->SetupLighting(lightColor, lightDir, lightStrength, ambientStrength);
		cube.GetComponent<LitMaterial>()->shader.SetVec3("viewPos", -camPos);
		cube.RenderUpdate();

		app.uiManager.Draw();

		glfwSwapBuffers(app.window.GetGLFWWindow());
	}
	app.Shutdown();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

