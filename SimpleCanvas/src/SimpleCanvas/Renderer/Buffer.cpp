#include "Buffer.h"

#include <glad/glad.h>

namespace sc
{
VertexBuffer::VertexBuffer(float * vertices, uint32_t size)
{
	glCreateBuffers(1, &rendererId);
	glBindBuffer(GL_ARRAY_BUFFER, rendererId);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &rendererId);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setLayout(BufferLayout const& pLayout)
{
    layout = pLayout;
}

BufferLayout VertexBuffer::getLayout() const
{
    return layout;
}

std::shared_ptr<VertexBuffer> VertexBuffer::create(float * vertices, uint32_t size)
{
    return std::make_shared<VertexBuffer>(vertices, size);
}

// INDEX BUFFER -------------------
IndexBuffer::IndexBuffer(uint32_t * indices, uint32_t count)
: _count(count)
{
    glCreateBuffers(1, &rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &rendererId);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

std::shared_ptr<IndexBuffer> IndexBuffer::create(uint32_t * indices, uint32_t count)
{
    return std::make_shared<IndexBuffer>(indices, count);
}

uint32_t IndexBuffer::count() const
{
    return _count;
}
} // namespace sc