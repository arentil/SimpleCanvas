#include "Shader.h"

#include <glad/glad.h>

namespace sc
{
Shader::Shader(std::string const& vertexSrc, std::string const& fragmentSrc)
{
    std::unordered_map<uint32_t, std::string> sources;
    sources[GL_VERTEX_SHADER] = vertexSrc;
    sources[GL_FRAGMENT_SHADER] = fragmentSrc;
    compile(sources);
}

Shader::~Shader()
{
    glDeleteProgram(_program);
}

void Shader::compile(std::unordered_map<uint32_t, std::string> const& shaderSources)
{
    GLuint program = glCreateProgram();
    std::vector<uint32_t> glShaderIds;
    glShaderIds.reserve(shaderSources.size());

    for (auto const &[type, source] : shaderSources)
    {
        GLuint shader = glCreateShader(type);

        const GLchar *source_c_str = (const GLchar *)source.c_str();
        glShaderSource(shader, 1, &source_c_str, 0);

        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
            
            glDeleteShader(shader);

            LOG_ERROR("Shader compilation failed! Error: %s", infoLog.data());
            break;
        }

        glAttachShader(program, shader);
        glShaderIds.push_back(shader);
    }

    _program = program;


    glLinkProgram(_program);

    GLint isLinked = 0;
    glGetProgramiv(_program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(_program, maxLength, &maxLength, &infoLog[0]);
        
        glDeleteProgram(_program);

        for (uint32_t shaderId : glShaderIds)
            glDeleteShader(shaderId);

        LOG_ERROR("Vertex or Fragment Shader linking failed! Error: %s", infoLog.data());
        return;
    }

    for (uint32_t shaderId : glShaderIds)
        glDetachShader(_program, shaderId);
}

void Shader::bind() const
{
    glUseProgram(_program);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::uploadUniformInt(std::string const& name, int value)
{
    GLint location = glGetUniformLocation(_program, name.c_str());
    glUniform1i(location, value);
}

void Shader::uploadUniformFloat(std::string const& name, float value)
{
    GLint location = glGetUniformLocation(_program, name.c_str());
    glUniform1f(location, value);
}

void Shader::uploadUniformFloat2(std::string const& name, scmath::Vec2 const& v)
{
    GLint location = glGetUniformLocation(_program, name.c_str());
    glUniform2f(location, v.x, v.y);
}

void Shader::uploadUniformFloat3(std::string const& name, scmath::Vec3 const& v)
{
    GLint location = glGetUniformLocation(_program, name.c_str());
    glUniform3f(location, v.x, v.y, v.z);
}

void Shader::uploadUniformFloat4(std::string const& name, scmath::Vec4 const& v)
{
    GLint location = glGetUniformLocation(_program, name.c_str());
    glUniform4f(location, v.x, v.y, v.z, v.w);
}

void Shader::uploadUniformMat4(std::string const& name, scmath::Mat4 const& m)
{
    GLint location = glGetUniformLocation(_program, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, m);
}

void ShadersContainer::addShader(std::string const& shaderName, ShaderPtr const& shader)
{
    if (_shaders.find(shaderName) != _shaders.end())
    {
        LOG_ERROR("ShaderContainer::addShader shader \"%s\" already exist!", shaderName.c_str())
        return;
    }

    _shaders.emplace(shaderName, shader);
}

void ShadersContainer::addShaderFromFile(std::string const& shaderName, std::string const& vertexShaderFilePath, std::string const& fragmentShaderFilePath)
{
    std::string const vertexSource = _fReader.readFile(vertexShaderFilePath);
    std::string const fragmentSource = _fReader.readFile(fragmentShaderFilePath);
    if (vertexSource.empty() || fragmentSource.empty())
    {
        LOG_ERROR("ShaderContainer::addShaderFromFile shader source empty!");
        return;
    }
    _shaders.emplace(shaderName, std::make_unique<Shader>(vertexSource, fragmentSource));
}

ShaderPtr ShadersContainer::getShader(std::string const& shaderName) const
{
    if (_shaders.find(shaderName) == _shaders.end())
    {
        LOG_ERROR("ShaderContainer::getShader no such shader \"%s\" in ShaderContainer!", shaderName.c_str());
    }
    return _shaders.at(shaderName);
}
} // namespace sc