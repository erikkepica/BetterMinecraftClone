#pragma once
#include<glad/glad.h>
#include<vector>

class VertexBufferElement
{
public:
	unsigned int count;
	unsigned int type;
	bool normalized;
	unsigned int offset;

	static unsigned int GetSize(unsigned int type)
	{
		switch (type)
		{
		case 5126: return 4;
		}
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride = 0;
public:
	template<typename T>
	void Push(unsigned int count)
	{
		LOG_ERROR("VERTEX BUFFER LAYOUT: unsuported type", true);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_FLOAT, GL_FALSE, m_Stride });
		m_Stride += count * VertexBufferElement::GetSize(GL_FLOAT);
	}

	void SetAttributes()
	{
		for (int i = 0; i < m_Elements.size(); i++)
		{
			GL_CALL_DEBUG(glVertexAttribPointer(i, m_Elements.at(i).count, m_Elements.at(i).type, m_Elements.at(i).normalized, m_Stride, (void*)m_Elements.at(i).offset));
			glEnableVertexAttribArray(i);
		}
	}
};


class VAO
{
private:
	unsigned int m_ID;
	VertexBufferLayout m_Attribs;
public:
	VAO()
		:m_ID(0)
	{
	}

	void DoAttribs(VertexBufferLayout& attribs)
	{
		m_Attribs = attribs;

		m_Attribs.SetAttributes();
	}

	~VAO()
	{
		GL_CALL_DEBUG(glDeleteVertexArrays(1, &m_ID));
	}

	void Generate()
	{
		GL_CALL_DEBUG(glGenVertexArrays(1, &m_ID));

		Bind();

		std::vector<unsigned int> attribSizes{ 3,2,3 };
	}

	void Bind()
	{
		GL_CALL_DEBUG(glBindVertexArray(m_ID));
	}

	static void Unbind()
	{
		GL_CALL_DEBUG(glBindVertexArray(0));
	}
};

