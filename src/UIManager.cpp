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

UIManager::UIManager(GLFWwindow* window)
{
	Init(window);
}

void UIManager::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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

DebugDrawElement::DebugDrawElement(void* dataPtr, std::string name)
	:m_DataPtr(dataPtr), m_Name(name)
{
}

void DebugDrawElement::Draw()
{
	return;
}

void* DebugDrawElement::GetDataPtr()
{
	return m_DataPtr;
}

std::string DebugDrawElement::GetName()
{
	return m_Name;
}

HeaderElement::HeaderElement(void* dataPtr, std::string name, std::vector<std::unique_ptr<DebugDrawElement>>& drawElements)
	: DebugDrawElement(dataPtr, name), m_DrawElements(std::move(drawElements))
{
}

void HeaderElement::Draw()
{
	if (ImGui::CollapsingHeader(GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		for (int i = 0; i < m_DrawElements.size(); i++)
		{
			m_DrawElements[i]->Draw();
		}
	}
}

void HeaderElement::Push(std::unique_ptr<DebugDrawElement> element)
{
	m_DrawElements.push_back(std::move(element));
}

Color3Element::Color3Element(void* dataPtr, std::string name)
	: DebugDrawElement(dataPtr, name) {}

void Color3Element::Draw()
{
	ImGui::ColorEdit3(GetName().c_str(), (float*)GetDataPtr());
}

Color4Element::Color4Element(void* dataPtr, std::string name)
	: DebugDrawElement(dataPtr, name) {}

void Color4Element::Draw()
{
	ImGui::ColorEdit4(GetName().c_str(), (float*)GetDataPtr());
}

BoolElement::BoolElement(void* dataPtr, std::string name)
	: DebugDrawElement(dataPtr, name)
{
}

void BoolElement::Draw()
{
	ImGui::Checkbox(GetName().c_str(), (bool*)GetDataPtr());
}
