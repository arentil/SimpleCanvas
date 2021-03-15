#pragma once

#include <SCMath.h>
#include "Utils/FileReader.h"

#include <string>

namespace sc
{
class Shader;
using ShaderPtr = std::shared_ptr<Shader>;

class Shader
{
public:
    Shader(std::string const& vertexSrc, std::string const& fragmentSrc);
    ~Shader();

    void bind() const;
    void unbind() const;

    void uploadUniformInt(std::string const& name, int value);
    void uploadUniformFloat(std::string const& name, float value);
    void uploadUniformFloat2(std::string const& name, scmath::Vec2 const& v);
    void uploadUniformFloat3(std::string const& name, scmath::Vec3 const& v);
    void uploadUniformFloat4(std::string const& name, scmath::Vec4 const& v);
    void uploadUniformMat4(std::string const& name, scmath::Mat4 const& m);
private:
    void compile(std::unordered_map<uint32_t, std::string> const& shaderSources);

    uint32_t _program;
    std::string _name;
};

class ShadersContainer
{
public:
    ShadersContainer() = default;
    ~ShadersContainer() = default;

    void addShader(std::string const& shaderName, ShaderPtr const& shader);
    void addShaderFromFile(std::string const& shaderName, std::string const& vertexShaderFilePath, std::string const& fragmentShaderFilePath);
    ShaderPtr getShader(std::string const& shaderName) const;

private:
    std::unordered_map<std::string, ShaderPtr> _shaders;
    FileReader _fReader;
};
} // namespace sc;