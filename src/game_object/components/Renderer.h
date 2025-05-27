#pragma once
#include"graphics/VertexArrayObject.h"
#include"graphics/VertexBufferObject.h"
#include"graphics/ElementBufferObject.h"
#include"Component.h"

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
	~Renderer(){}

	void Generate(std::vector<float> vertices, std::vector<unsigned int> indices, VertexBufferLayout& attribs);

	void SetVertices(std::vector<float> vertices);
	
	void SetIndices(std::vector<unsigned int> indices);

	void Draw();

	virtual void AddDebugToWindow(DebugWindow& win) override { return; }

};