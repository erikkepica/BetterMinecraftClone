#pragma once
#include<glad/glad.h>
#include<vector>

class VBO
{
public:
    VBO()
        :m_ID(0)
    {
    }

    void Generate(const std::vector<float>& vertices)
    {
        GL_CALL_DEBUG(glGenBuffers(1, &m_ID));
        Bind();
        UpdateData(vertices);
    }

    void UpdateData(const std::vector<float>& vertices)
    {
        m_Vertices = vertices;
        m_BufferData();
    }

    void Bind() { GL_CALL_DEBUG(glBindBuffer(GL_ARRAY_BUFFER, m_ID)); }
    static void UnBind() { GL_CALL_DEBUG(glBindBuffer(GL_ARRAY_BUFFER, 0)); }

    ~VBO()
    {
        if (m_ID != 0)
            GL_CALL_DEBUG(glDeleteBuffers(1, &m_ID));
    }
private:
    unsigned int m_ID;

    std::vector<float> m_Vertices;

    void m_BufferData()
    {
        float* verticesArr = m_Vertices.data();
        GL_CALL_DEBUG(glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), verticesArr, GL_STATIC_DRAW));
    }
};