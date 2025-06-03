#include"VertexBufferObject.h"

void VBO::Generate(std::vector<float>& vertices)
{
    GL_CALL_DEBUG(glGenBuffers(1, &m_ID));
    Bind();
    BufferData(vertices);
}

void VBO::Bind()
{
    GL_CALL_DEBUG(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

void VBO::UnBind()
{
    GL_CALL_DEBUG(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VBO::~VBO()
{
    if (m_ID != 0)
        GL_CALL_DEBUG(glDeleteBuffers(1, &m_ID));
}

void VBO::BufferData(std::vector<float>& vertices)
{
    float* verticesArr = vertices.data();
    GL_CALL_DEBUG(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), verticesArr, GL_STATIC_DRAW));
}
