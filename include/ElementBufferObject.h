#pragma once
#include<glad/glad.h>
#include<vector>

class EBO
{
public:
    EBO()
        :m_ID(0)
    {
    }

    void Generate(const std::vector<unsigned int>& indices)
    {
        GL_CALL_DEBUG(glGenBuffers(1, &m_ID));
        Bind();
        UpdateData(indices);
    }

    void UpdateData(const std::vector<unsigned int>& indices)
    {
        m_Indices = indices;
        m_BufferData();
    }

    void Bind(){ GL_CALL_DEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));}
    static void UnBind() { GL_CALL_DEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); }

    unsigned int GetIndicesNum() { return m_Indices.size(); }

    ~EBO()
    {
        if (m_ID != 0)
            GL_CALL_DEBUG(glDeleteBuffers(1, &m_ID));
    }
private:
    unsigned int m_ID;

    std::vector<unsigned int> m_Indices;

    void m_BufferData()
    {
        unsigned int* indicesArr = m_Indices.data();
        GL_CALL_DEBUG(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), indicesArr, GL_STATIC_DRAW));
    }
};