#pragma once
#include"glad/glad.h"
#include"stb_image/stb_image.h"

#include"Logging.h"

#include"UIManager.h"




class Texture
{
public:
    Texture()
    {
    }
    Texture(std::string path)
    {
        Generate(path);
    }

    void Generate(std::string path);

    void Bind() { glBindTexture(GL_TEXTURE_2D, m_ID); };

    unsigned int GetID() { return m_ID; }
    char PathBuff[128]{ " " };
private:
    unsigned int m_ID;
};


class ListOpenGLTextureElements : public DebugDrawElement
{
public:
    int size;

    ListOpenGLTextureElements(void* dataPtr, std::string name, int size)
        :DebugDrawElement(dataPtr, name), size(size)
    {}

    virtual void Draw() override
    {

        for (int i = 0; i < size; ++i) {
            Texture& tex = ((Texture*)GetDataPtr())[i];
            ImGui::PushID(i);

            std::string txt("Texture " + i);

            ImGui::Text(txt.c_str());
            ImGui::InputText("Location: ", tex.PathBuff, 128);
            if (ImGui::Button("Generate Image", ImVec2(128, 32)))
            {
                tex.Generate(std::string(tex.PathBuff));
            }

            if (tex.GetID() != 0)
            {
                ImGui::Image(
                    (void*)(intptr_t)tex.GetID(),
                    ImVec2(128, 128));
            }


            ImGui::Spacing();
            ImGui::Separator();

            ImGui::PopID();
        }
    }
};