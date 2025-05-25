#include"UIManager.h"
#include"Logging.h"

void UIManager::Init(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


	if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
	{
		LOG_ERROR("IMGUI: Failed to init glfw for imgui", true);
		return;
	}
	if (!ImGui_ImplOpenGL3_Init())
	{
		LOG_ERROR("IMGUI: Failed to init opengl for imgui", true);
		return;
	}
	LOG_INFO("Initialized IMGUI");
}

void UIManager::Draw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	for (auto win : m_DebugWindows)
	{
		win->Draw();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DebugWindow::Draw()
{
	ImGui::Begin(m_Name.c_str(), &m_Enabled, ImGuiWindowFlags_MenuBar);
	for (int i = 0; i < m_DrawElements.size(); i++)
	{
		m_DrawElements[i]->Draw();
	}
	ImGui::End();
}