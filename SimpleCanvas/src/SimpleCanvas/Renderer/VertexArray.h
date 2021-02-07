#pragma once

#include "Buffer.h"

namespace sc
{
class VertexArray;
using VertexArrayPtr = std::shared_ptr<VertexArray>;

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addVertexBuffer(VertexBufferPtr const& vertexBuffer);
    void setIndexBuffer(IndexBufferPtr const& indexBuffer);
    const VertexBufferPtrVec& getVertexBuffers() const { return _vertexBuffers; }
    const IndexBufferPtr& getIndexBuffer() const { return _indexBuffer; }

    static VertexArray* create();

private:
    uint32_t _rendererId;
    VertexBufferPtrVec _vertexBuffers;
    IndexBufferPtr _indexBuffer;
};
} // namespace sc