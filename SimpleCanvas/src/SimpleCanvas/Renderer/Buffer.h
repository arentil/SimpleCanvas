#pragma once

namespace sc
{
class VertexBuffer
{
public:
    VertexBuffer(float * vertices, uint32_t size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

    static std::unique_ptr<VertexBuffer> create(float * vertices, uint32_t size);

private:
    uint32_t rendererId;
};

class IndexBuffer
{
public:
    IndexBuffer(uint32_t * indices, uint32_t count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    static std::unique_ptr<IndexBuffer> create(uint32_t * indices, uint32_t count);

private:
    uint32_t rendererId;
};

} // namespace sc