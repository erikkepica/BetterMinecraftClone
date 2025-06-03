#pragma once
#include<glad/glad.h>
#include<vector>
#include"Logging.h"

class VBO
{
public:
    VBO()
        :m_ID(0)
    {
    }

    void Generate(std::vector<float>& vertices);

    void BufferData(std::vector<float>& vertices);

    void Bind();
    static void UnBind();

    ~VBO();
private:
    unsigned int m_ID;
};