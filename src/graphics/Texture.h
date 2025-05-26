#pragma once
#include"glad/glad.h"
#include"stb_image/stb_image.h"

#include"Logging.h"

class Texture
{
public:
    Texture()
    {
    }
    Texture(const char* path)
    {
        Generate(path);
    }

    void Generate(const char* path);

    void Bind() { glBindTexture(GL_TEXTURE_2D, m_ID); };
private:
    unsigned int m_ID;
};