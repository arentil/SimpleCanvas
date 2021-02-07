#pragma once

#include <SCMath.h>

#include <string>

namespace sc
{
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
    uint32_t program;
};
} // namespace sc;