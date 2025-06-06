#include"Texture.h"
#include<string>
#include<map>

Texture::Texture()
{
}
Texture::Texture(std::string path)
{
    Generate(path);
}
void Texture::Generate(std::string path)
{
    memcpy(PathBuff, path.c_str(), path.size());

    stbi_set_flip_vertically_on_load(true);

    GL_CALL_DEBUG(glGenTextures(1, &m_ID));
    Bind();
    GL_CALL_DEBUG_ERR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL_DEBUG_ERR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CALL_DEBUG_ERR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CALL_DEBUG_ERR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));


    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);
    if (data)
    {
        GL_CALL_DEBUG_ERR(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
        GL_CALL_DEBUG_ERR(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else
    {
        LOG_WARNING("TEXTURE: Failed to load texture: " << path);
    }
    stbi_image_free(data);
}

void Texture::Bind(unsigned int glWhatTex)
{
    GL_CALL_DEBUG(glActiveTexture(GL_TEXTURE0+glWhatTex));
    GL_CALL_DEBUG_ERR(glBindTexture(GL_TEXTURE_2D, m_ID));
}
void Texture::Bind()
{
    GL_CALL_DEBUG(glBindTexture(GL_TEXTURE_2D, m_ID));
}

unsigned int Texture::GetID()
{
    return m_ID;
}

ListOpenGLTextureElements::ListOpenGLTextureElements(void* dataPtr, std::string name, int size)
    :DebugDrawElement(dataPtr, name), size(size)
{
}

void ListOpenGLTextureElements::Draw()
{
    auto texMap = static_cast<std::map<std::string, Texture>*>(GetDataPtr());

    int i = 0;
    for (auto& [name, tex] : *texMap)
    {
        ImGui::PushID(i);

        ImGui::Text("Texture: %s", name.c_str());
        ImGui::InputText("Location", tex.PathBuff, 128);

        if (ImGui::Button("Generate Image", ImVec2(128, 32)))
        {
            tex.Generate(std::string(tex.PathBuff));
        }

        if (tex.GetID() != 0)
        {
            ImGui::Image((void*)(intptr_t)tex.GetID(), ImVec2(128, 128));
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::PopID();

        ++i;
    }
}