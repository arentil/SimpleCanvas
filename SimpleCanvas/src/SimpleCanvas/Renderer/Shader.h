#pragma once

#include <SCMath.h>

#include <string>

namespace sc
{
class Shader;
using ShaderPtr = std::shared_ptr<Shader>;

class Shader
{
public:
    Shader(std::string const& filePath);
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
    std::string readFile(std::string const& filePath);
    std::unordered_map<uint32_t, std::string> preprocess(std::string const& source);
    void compile(std::unordered_map<uint32_t, std::string> const& shaderSources);

    uint32_t _program; 
};
} // namespace sc;