#include"ElementBufferObject.h"

EBO::EBO()
    :m_ID(0)
{
}

void EBO::Generate(const std::vector<unsigned int>& indices)
{
    GL_CALL_DEBUG(glGenBuffers(1, &m_ID));
    Bind();
    UpdateData(indices);
}

void EBO::UpdateData(const std::vector<unsigned int>& indices)
{
    m_Indices = indices;
    m_BufferData();
}

void EBO::Bind()
{
    GL_CALL_DEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}

void EBO::UnBind()
{
    GL_CALL_DEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int EBO::GetIndicesNum()
{
    return m_Indices.size();
}

EBO::~EBO()
{
    if (m_ID != 0)
        GL_CALL_DEBUG(glDeleteBuffers(1, &m_ID));
}

void EBO::m_BufferData()
{
    unsigned int* indicesArr = m_Indices.data();
    GL_CALL_DEBUG(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), indicesArr, GL_STATIC_DRAW));
}
