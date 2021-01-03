#pragma once

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
private:
    uint32_t program;
};
} // namespace sc;