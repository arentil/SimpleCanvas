#include "VertexArray.h"

#include <glad/glad.h>

namespace sc
{
static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float:     return GL_FLOAT;
		case ShaderDataType::Float2:    return GL_FLOAT;
		case ShaderDataType::Float3:    return GL_FLOAT;
		case ShaderDataType::Float4:    return GL_FLOAT;
		case ShaderDataType::Int:       return GL_INT;
		case ShaderDataType::Int2:      return GL_INT;
		case ShaderDataType::Int3:      return GL_INT;
		case ShaderDataType::Int4:      return GL_INT;
		case ShaderDataType::Mat3:      return GL_FLOAT;
		case ShaderDataType::Mat4:      return GL_FLOAT;
		case ShaderDataType::Bool:      return GL_BOOL;
	}
	return 0;
}

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &_rendererId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_rendererId);
}

VertexArray* VertexArray::create()
{
    return new VertexArray();
}

void VertexArray::bind() const
{
    glBindVertexArray(_rendererId);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::addVertexBuffer(std::shared_ptr<VertexBuffer> const& vertexBuffer)
{
    glBindVertexArray(_rendererId);
    vertexBuffer->bind();

    uint32_t index = 0;
    const auto& layout = vertexBuffer->getLayout();
	for (auto const& element : vertexBuffer->getLayout())
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			element.getComponentCount(),
			shaderDataTypeToOpenGLBaseType(element.type),
			element.normalized ? GL_TRUE : GL_FALSE,
			layout.getStride(),
			(const void*)element.offset);
		index++;
	}
    _vertexBuffers.push_back(vertexBuffer);
}

void VertexArray::setIndexBuffer(std::shared_ptr<IndexBuffer> const& indexBuffer)
{
    glBindVertexArray(_rendererId);
    indexBuffer->bind();
    _indexBuffer = indexBuffer;
}
} // namespace sc