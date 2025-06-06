#include"Renderer.h"

Renderer::Renderer(std::vector<float> vertices, std::vector<unsigned int> indices, VertexBufferLayout& attribs)
{
	Generate(vertices, indices, attribs);
}

Renderer::Renderer(Model model)
{
	Generate(model.GetVertices(), model.GetIndices(), model.GetAttributes());
}

void Renderer::Generate(std::vector<float> vertices, std::vector<unsigned int> indices, VertexBufferLayout& attribs)
{
	m_VAO.Generate();
	m_VBO.Generate(vertices);
	m_EBO.Generate(indices);
	m_VAO.DoAttribs(attribs);

	VBO::UnBind();
	VAO::Unbind();
	EBO::UnBind();
}

void Renderer::SetVertices(std::vector<float> vertices)
{
	m_VBO.BufferData(vertices);
}

void Renderer::SetIndices(std::vector<unsigned int> indices)
{
	m_EBO.UpdateData(indices);
}

void Renderer::SetModel(Model model)
{
}

void Renderer::Draw()
{
	m_EBO.Bind();
	m_VAO.Bind();
	glDrawElements(GL_TRIANGLES, m_EBO.GetIndicesNum(), GL_UNSIGNED_INT, 0);
	VAO::Unbind();
	EBO::UnBind();
}