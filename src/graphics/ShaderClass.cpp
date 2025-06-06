#include"ShaderClass.h"

Shader::Shader()
    :m_ID(0)
{
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    Generate(vertexPath, fragmentPath);
}

Shader::~Shader()
{
    GL_CALL_DEBUG(glDeleteProgram(m_ID));
}

void Shader::Generate(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    try
    {
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        LOG_ERROR("SHADER_CLASS: file not succesfully read: " << e.what(), true);
        return;
    }


    const char* vertexCodeChar = vertexCode.c_str();
    const char* fragmentCodeChar = fragmentCode.c_str();

    unsigned int vertexShader = GL_CALL_DEBUG(glCreateShader(GL_VERTEX_SHADER));
    GL_CALL_DEBUG_ERR(glShaderSource(vertexShader, 1, &vertexCodeChar, NULL));
    GL_CALL_DEBUG_ERR(glCompileShader(vertexShader));

    char infoLog[512];
    int success;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOG_ERROR("VERTEX_SHADER: compilation failed: " << infoLog, true);
        return;
    }

    unsigned int fragmentShader = GL_CALL_DEBUG_ERR(glCreateShader(GL_FRAGMENT_SHADER));
    GL_CALL_DEBUG_ERR(glShaderSource(fragmentShader, 1, &fragmentCodeChar, NULL));
    GL_CALL_DEBUG_ERR(glCompileShader(fragmentShader));

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOG_ERROR("FRAGMENT_SHADER: compilation failed: " << infoLog, true);
        return;
    }

    m_ID = GL_CALL_DEBUG_ERR(glCreateProgram());
    GL_CALL_DEBUG_ERR(glAttachShader(m_ID, vertexShader));
    GL_CALL_DEBUG_ERR(glAttachShader(m_ID, fragmentShader));
    GL_CALL_DEBUG_ERR(glLinkProgram(m_ID));

    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        LOG_ERROR("PROGRAM: linking failed: " << infoLog, true);
        return;
    }
    GL_CALL_DEBUG_ERR(glDeleteShader(vertexShader));
    GL_CALL_DEBUG_ERR(glDeleteShader(fragmentShader));

    return;
}

void Shader::Use()
{
    GL_CALL_DEBUG(glUseProgram(m_ID));
}

void Shader::SetBool(const std::string& name, bool value) const
{
    GL_CALL_DEBUG(glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value));
}

void Shader::SetInt(const std::string& name, int value) const
{
    GL_CALL_DEBUG(glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value));
}

void Shader::SetFloat(const std::string& name, float value) const
{
    GL_CALL_DEBUG(glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value));
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
    GL_CALL_DEBUG(glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]));
}

void Shader::SetVec2(const std::string& name, float x, float y) const
{
    GL_CALL_DEBUG(glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y));
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    GL_CALL_DEBUG(glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]));
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
    GL_CALL_DEBUG(glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z));
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
    GL_CALL_DEBUG(glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]));
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w)
{
    GL_CALL_DEBUG(glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w));
}

void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
    GL_CALL_DEBUG(glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
}

void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
    GL_CALL_DEBUG(glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
    GL_CALL_DEBUG(glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
}
