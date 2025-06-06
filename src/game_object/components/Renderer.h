#pragma once
#include"graphics/VertexArrayObject.h"
#include"graphics/VertexBufferObject.h"
#include"graphics/ElementBufferObject.h"
#include"Component.h"
#include"game_object/Model.h"

class Renderer : public Component
{
private:
	VAO m_VAO;
	VBO m_VBO;
	EBO m_EBO;
public:
	Renderer()
	{
	}
	Renderer(std::vector<float> vertices, std::vector<unsigned int> indices, VertexBufferLayout& attribs);
	Renderer(Model model);
	~Renderer(){}

	void Generate(std::vector<float> vertices, std::vector<unsigned int> indices, VertexBufferLayout& attribs);

	void SetVertices(std::vector<float> vertices);
	
	void SetIndices(std::vector<unsigned int> indices);

	void SetModel(Model model);

	void Draw();

	virtual void AddDebugToDrawArray(std::vector<std::unique_ptr<DebugDrawElement>>& win) override { return; }
	static std::string ID() { return "RENDERER"; }
	virtual std::string GetID() override { return ID(); }
};