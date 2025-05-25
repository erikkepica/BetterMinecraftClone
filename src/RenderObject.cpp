#include"RenderObject.h"

void RenderObject::Generate(std::vector<float> vertices, std::vector<unsigned int> indices, VertexBufferLayout& attribs)
{
	m_VAO.Generate();
	m_VBO.Generate(vertices);
	m_EBO.Generate(indices);
	m_VAO.DoAttribs(attribs);

	VBO::UnBind();
	VAO::Unbind();
	EBO::UnBind();
}

void RenderObject::Draw()
{
	m_EBO.Bind();
	m_VAO.Bind();
	glDrawElements(GL_TRIANGLES, m_EBO.GetIndicesNum(), GL_UNSIGNED_INT, 0);
	VAO::Unbind();
	EBO::UnBind();
}