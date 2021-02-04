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

    void uploadUniformMat4(std::string const& name, scmath::Mat4 const& mat);
private:
    uint32_t program;
};
} // namespace sc;