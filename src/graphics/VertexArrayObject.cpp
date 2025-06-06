#include "VertexArrayObject.h"

unsigned int VertexBufferElement::GetSize(unsigned int type)
{
	switch (type)
	{
	case GL_FLOAT: return 4;
	}
	return 0;
}

void VertexBufferLayout::SetAttributes()
{
	for (int i = 0; i < m_Elements.size(); i++)
	{
		GL_CALL_DEBUG(glVertexAttribPointer(i, m_Elements.at(i).count, m_Elements.at(i).type, m_Elements.at(i).normalized, m_Stride, (void*)m_Elements.at(i).offset));
		GL_CALL_DEBUG_ERR(glEnableVertexAttribArray(i));
	}
}

VAO::VAO()
	:m_ID(0)
{
}

void VAO::DoAttribs(VertexBufferLayout& attribs)
{
	m_Attribs = attribs;

	m_Attribs.SetAttributes();
}

VAO::~VAO()
{
	GL_CALL_DEBUG(glDeleteVertexArrays(1, &m_ID));
}

void VAO::Generate()
{
	GL_CALL_DEBUG(glGenVertexArrays(1, &m_ID));

	Bind();
}

void VAO::Bind()
{
	GL_CALL_DEBUG(glBindVertexArray(m_ID));
}

void VAO::Unbind()
{
	GL_CALL_DEBUG(glBindVertexArray(0));
}
