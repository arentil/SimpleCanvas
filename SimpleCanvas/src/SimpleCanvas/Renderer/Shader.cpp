#include "Shader.h"

#include <fstream>
#include <cassert>
#include <glad/glad.h>

namespace sc
{
static GLenum shaderTypeFromString(std::string const& type)
{
    if (type == "vertex") return GL_VERTEX_SHADER;
    if (type == "fragment") return GL_FRAGMENT_SHADER;

    assert(false && "Unknown shader type!");
}

Shader::Shader(std::string const& filePath)
{
    std::string source = readFile(filePath);
    auto shaderSources = preprocess(source);
    compile(shaderSources);
}

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

std::string Shader::readFile(std::string const& filePath)
{
    std::string result;
    std::ifstream in(filePath, std::ios::in, std::ios::binary);
    if (in)
    {
        in.seekg(0, std::ios::end);
        result.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0], result.size());
        in.close();
    }
    else
    {
        LOG_ERROR("Could not open file \'%s\'", filePath.c_str());
    }
    return result;
}

std::unordered_map<uint32_t, std::string> Shader::preprocess(std::string const& source)
{
    std::unordered_map<uint32_t, std::string> shaderSources;
    
    const char * typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0);
    while (pos != std::string::npos)
    {
        size_t eol = source.find_first_of("\r\n", pos);
        assert(eol != std::string::npos && "Syntax error!");
        size_t begin = pos + typeTokenLength + 1;
        std::string type = source.substr(begin, eol - begin);
        assert((type == "vertex" | type == "fragment") && "Invalid shader type specified");

        size_t nextLinePos = source.find_first_not_of("\r\n", eol);
        pos = source.find(typeToken, nextLinePos);
        shaderSources[shaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
    }

    return shaderSources;
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
} // namespace sc