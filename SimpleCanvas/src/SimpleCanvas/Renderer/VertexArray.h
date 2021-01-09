#pragma once

#include "Buffer.h"

namespace sc
{
class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addVertexBuffer(std::shared_ptr<VertexBuffer> const& vertexBuffer);
    void setIndexBuffer(std::shared_ptr<IndexBuffer> const& indexBuffer);
    const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const { return _vertexBuffers; }
    const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return _indexBuffer; }

    static VertexArray* create();

private:
    uint32_t _rendererId;
    std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
    std::shared_ptr<IndexBuffer> _indexBuffer;
};
} // namespace sc