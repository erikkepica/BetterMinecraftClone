#pragma once
#include<GLFW/glfw3.h>
#include <imgui.h>
#include<backends/imgui_impl_glfw.h>
#include<backends/imgui_impl_opengl3.h>
#include<vector>
#include<string>
#include<numeric>
#include<memory>

class DebugDrawElement
{
public:
	DebugDrawElement(void* dataPtr, std::string name);


	virtual void Draw();

	void* GetDataPtr();
	std::string GetName();

private:
	void* m_DataPtr;
	std::string m_Name;
};

class HeaderElement : public DebugDrawElement
{
private:
	std::vector<std::unique_ptr<DebugDrawElement>> m_DrawElements;
public:

	HeaderElement(void* dataPtr, std::string name, std::vector<std::unique_ptr<DebugDrawElement>>& drawElements);
	void Draw() override;
	void Push(std::unique_ptr<DebugDrawElement> element);
};

class Color3Element : public DebugDrawElement { public: Color3Element(void* dataPtr, std::string name); void Draw() override; };
class Color4Element : public DebugDrawElement { public: Color4Element(void* dataPtr, std::string name); void Draw() override; };

class BoolElement : public DebugDrawElement { public: BoolElement(void* dataPtr, std::string name); void Draw() override; };

class DragFloat1ElementInf : public DebugDrawElement { public: DragFloat1ElementInf(void* dataPtr, std::string name) : DebugDrawElement(dataPtr, name) {} void Draw() override { ImGui::DragFloat(GetName().c_str(), (float*)GetDataPtr(), 0.1f, -std::numeric_limits<float>().infinity(), std::numeric_limits<float>().infinity()); } };
class DragFloat2ElementInf : public DebugDrawElement { public: DragFloat2ElementInf(void* dataPtr, std::string name) : DebugDrawElement(dataPtr, name) {} void Draw() override { ImGui::DragFloat2(GetName().c_str(), (float*)GetDataPtr(), 0.1f, -std::numeric_limits<float>().infinity(), std::numeric_limits<float>().infinity()); } };
class DragFloat3ElementInf : public DebugDrawElement { public: DragFloat3ElementInf(void* dataPtr, std::string name) : DebugDrawElement(dataPtr, name) {} void Draw() override { ImGui::DragFloat3(GetName().c_str(), (float*)GetDataPtr(), 0.1f, -std::numeric_limits<float>().infinity(), std::numeric_limits<float>().infinity()); } };
class DragFloat4ElementInf : public DebugDrawElement { public: DragFloat4ElementInf(void* dataPtr, std::string name) : DebugDrawElement(dataPtr, name) {} void Draw() override { ImGui::DragFloat4(GetName().c_str(), (float*)GetDataPtr(), 0.1f, -std::numeric_limits<float>().infinity(), std::numeric_limits<float>().infinity()); } };

class DragFloat1ElementRange : public DebugDrawElement {
public:
	float minVal=0;
	float maxVal=0;
	DragFloat1ElementRange(void* dataPtr, std::string name, float min, float max)
		:DebugDrawElement(dataPtr,name), minVal(min), maxVal(max)
	{}
	void Draw() override { ImGui::DragFloat(GetName().c_str(), (float*)GetDataPtr(), 0.1f, minVal, maxVal); }
};
class DragFloat2ElementRange : public DebugDrawElement {
public:
	float minVal=0;
	float maxVal=0;
	DragFloat2ElementRange(void* dataPtr, std::string name, float min, float max)
		:DebugDrawElement(dataPtr,name), minVal(min), maxVal(max)
	{}
	void Draw() override { ImGui::DragFloat2(GetName().c_str(), (float*)GetDataPtr(), 0.1f, minVal, maxVal); }
};
class DragFloat3ElementRange : public DebugDrawElement {
public:
	float minVal=0;
	float maxVal=0;
	DragFloat3ElementRange(void* dataPtr, std::string name, float min, float max)
		:DebugDrawElement(dataPtr,name), minVal(min), maxVal(max)
	{}
	void Draw() override { ImGui::DragFloat3(GetName().c_str(), (float*)GetDataPtr(), 0.1f, minVal, maxVal); }
};
class DragFloat4ElementRange : public DebugDrawElement {
public:
	float minVal=0;
	float maxVal=0;
	DragFloat4ElementRange(void* dataPtr, std::string name, float min, float max)
		:DebugDrawElement(dataPtr,name), minVal(min), maxVal(max)
	{}
	void Draw() override { ImGui::DragFloat4(GetName().c_str(), (float*)GetDataPtr(), 0.1f, minVal, maxVal); }
};


class DebugWindow
{
private:
	std::string m_Name = "";
	ImGuiWindowFlags m_Flags = 0;
	bool m_Enabled = true;

	std::vector<std::unique_ptr<DebugDrawElement>> m_DrawElements;

public:
	inline static unsigned int defaultCount = 0;
	DebugWindow()
		:m_Name(std::string("default") + std::to_string(defaultCount))
	{
		defaultCount += 1;
	}
	DebugWindow(const char* name, ImGuiWindowFlags flags)
		:m_Name(name),m_Flags(flags)
	{
	}
	~DebugWindow(){}
	
	void Push(std::unique_ptr<DebugDrawElement> element) { m_DrawElements.push_back(std::move(element)); }

	void Draw();
};

class UIManager
{
private:
	std::vector<DebugWindow*> m_DebugWindows;
public:
	UIManager(){}
	~UIManager()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Draw();

	void Push(DebugWindow* window) { m_DebugWindows.push_back(window); }

	void Init(GLFWwindow* window);
};