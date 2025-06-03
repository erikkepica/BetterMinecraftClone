#pragma once
#include"glad/glad.h"
#include"stb_image/stb_image.h"

#include"Logging.h"

#include"UIManager.h"



class Texture
{
public:
    Texture();
    Texture(std::string path);

    void Generate(std::string path);

    void Bind(unsigned int glWhatTex);
    void Bind();

    unsigned int GetID();
    char PathBuff[128]{ " " };
private:
    unsigned int m_ID;
};


class ListOpenGLTextureElements : public DebugDrawElement
{
public:
    int size;

    ListOpenGLTextureElements(void* dataPtr, std::string name, int size);

    virtual void Draw() override;
};