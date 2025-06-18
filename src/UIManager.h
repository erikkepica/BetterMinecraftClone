#pragma once
#include<GLFW/glfw3.h>
#include <imgui.h>
#include<backends/imgui_impl_glfw.h>
#include<backends/imgui_impl_opengl3.h>
#include<vector>
#include<string>
#include<numeric>
#include<memory>
#include<Event.h>
#include"Logging.h"

class DebugDrawElement
{
public:
	DebugDrawElement(void* dataPtr, std::string name);
	

	Event change;

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

class DragFloat1ElementInf : public DebugDrawElement { public: DragFloat1ElementInf(void* dataPtr, std::string name) : DebugDrawElement(dataPtr, name) {} void Draw() override { DebugDrawElement::Draw(); if (ImGui::DragFloat(GetName().c_str(), (float*)GetDataPtr(), 0.1f, -std::numeric_limits<float>().infinity(), std::numeric_limits<float>().infinity())) { change.Induce(this); } } };
class DragFloat2ElementInf : public DebugDrawElement { public: DragFloat2ElementInf(void* dataPtr, std::string name) : DebugDrawElement(dataPtr, name) {} void Draw() override { DebugDrawElement::Draw(); if (ImGui::DragFloat2(GetName().c_str(), (float*)GetDataPtr(), 0.1f, -std::numeric_limits<float>().infinity(), std::numeric_limits<float>().infinity())) { change.Induce(this); } } };
class DragFloat3ElementInf : public DebugDrawElement { public: DragFloat3ElementInf(void* dataPtr, std::string name) : DebugDrawElement(dataPtr, name) {} void Draw() override { DebugDrawElement::Draw(); if (ImGui::DragFloat3(GetName().c_str(), (float*)GetDataPtr(), 0.1f, -std::numeric_limits<float>().infinity(), std::numeric_limits<float>().infinity())) { change.Induce(this); } } };
class DragFloat4ElementInf : public DebugDrawElement { public: DragFloat4ElementInf(void* dataPtr, std::string name) : DebugDrawElement(dataPtr, name) {} void Draw() override { DebugDrawElement::Draw(); if (ImGui::DragFloat4(GetName().c_str(), (float*)GetDataPtr(), 0.1f, -std::numeric_limits<float>().infinity(), std::numeric_limits<float>().infinity())) { change.Induce(this); } } };

class DragFloat1ElementRange : public DebugDrawElement {
public:
	float minVal=0;
	float maxVal=0;
	DragFloat1ElementRange(void* dataPtr, std::string name, float min, float max)
		:DebugDrawElement(dataPtr,name), minVal(min), maxVal(max)
	{}
	void Draw() override { DebugDrawElement::Draw(); if (ImGui::DragFloat(GetName().c_str(), (float*)GetDataPtr(), 0.1f, minVal, maxVal)) { change.Induce(this); } }
};
class DragFloat2ElementRange : public DebugDrawElement {
public:
	float minVal=0;
	float maxVal=0;
	DragFloat2ElementRange(void* dataPtr, std::string name, float min, float max)
		:DebugDrawElement(dataPtr,name), minVal(min), maxVal(max)
	{}
	void Draw() override { DebugDrawElement::Draw(); if (ImGui::DragFloat2(GetName().c_str(), (float*)GetDataPtr(), 0.1f, minVal, maxVal)) { change.Induce(this); } }
};
class DragFloat3ElementRange : public DebugDrawElement {
public:
	float minVal=0;
	float maxVal=0;
	DragFloat3ElementRange(void* dataPtr, std::string name, float min, float max)
		:DebugDrawElement(dataPtr,name), minVal(min), maxVal(max)
	{}
	void Draw() override { DebugDrawElement::Draw(); if (ImGui::DragFloat3(GetName().c_str(), (float*)GetDataPtr(), 0.1f, minVal, maxVal)) { change.Induce(this); } }
};
class DragFloat4ElementRange : public DebugDrawElement {
public:
	float minVal=0;
	float maxVal=0;
	DragFloat4ElementRange(void* dataPtr, std::string name, float min, float max)
		:DebugDrawElement(dataPtr,name), minVal(min), maxVal(max)
	{}
	void Draw() override { DebugDrawElement::Draw(); if (ImGui::DragFloat4(GetName().c_str(), (float*)GetDataPtr(), 0.1f, minVal, maxVal)) { change.Induce(this); } }
};

class DropdownElement : public DebugDrawElement {
private:
	int *m_CurrentItem;
	std::vector<const char*> m_Items;
public:

	DropdownElement(void* dataPtr, std::string name, std::vector<const char*> items, int* currentItem)
		:DebugDrawElement(dataPtr, name), m_CurrentItem(currentItem), m_Items(items)
	{}
	void Draw() override {
		DebugDrawElement::Draw();
		if (ImGui::Combo(GetName().c_str(), m_CurrentItem, m_Items.data(), (int)m_Items.size())) 
		{ change.Induce(this); };
	}
};

class DebugWindow
{
private:
	std::string m_Name = "";
	ImGuiWindowFlags m_Flags = 0;
	bool m_Enabled = true;

	std::vector<std::unique_ptr<DebugDrawElement>> m_DrawElements;

public:
	Event change;
	inline static unsigned int defaultCount = 0;
	DebugWindow()
		:m_Name(std::string("default") + std::to_string(defaultCount))
	{
		defaultCount += 1;
	}
	DebugWindow(const char* name, ImGuiWindowFlags flags)
		:m_Name(name), m_Flags(flags)
	{
	}

	~DebugWindow(){}
	
	void Push(std::unique_ptr<DebugDrawElement> element) { m_DrawElements.push_back(std::move(element)); }

	void Clear();

	void Draw();
};

class UIManager
{
private:
	std::vector<DebugWindow*> m_DebugWindows;
public:

	UIManager(){}
	UIManager(GLFWwindow* window);

	void Shutdown();

	void Draw();

	void Push(DebugWindow* window) { m_DebugWindows.push_back(window); }

	void Init(GLFWwindow* window);
};