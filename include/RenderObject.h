#pragma once
#include"Logging.h"
#include"VertexArrayObject.h"
#include"VertexBufferObject.h"
#include"ElementBufferObject.h"
#include"Material.h"

class RenderObject
{
private:
	VAO m_VAO;
	VBO m_VBO;
	EBO m_EBO;
public:
	RenderObject()
	{
	}
	RenderObject(std::vector<float> vertices, std::vector<unsigned int> indices, VertexBufferLayout& attribs)
	{
		Generate(vertices, indices, attribs);
	}
	~RenderObject(){}

	void Generate(std::vector<float> vertices, std::vector<unsigned int> indices, VertexBufferLayout& attribs);

	void SetVertices(std::vector<float> vertices)
	{
		m_VBO.UpdateData(vertices);
	}	
	
	void SetIndices(std::vector<unsigned int> indices)
	{
		m_EBO.UpdateData(indices);
	}

	void Draw();
};