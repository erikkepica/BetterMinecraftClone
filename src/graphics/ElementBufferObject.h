#pragma once
#include<glad/glad.h>
#include<vector>
#pragma once
#include"Logging.h"

class EBO
{
public:
    EBO();

    void Generate(const std::vector<unsigned int>& indices);

    void UpdateData(const std::vector<unsigned int>& indices);

    void Bind();
    static void UnBind();

    unsigned int GetIndicesNum();

    ~EBO();
private:
    unsigned int m_ID;

    std::vector<unsigned int> m_Indices;

    void m_BufferData();
};