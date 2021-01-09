#pragma once

namespace sc
{

enum class ShaderDataType : uint8_t
{
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int, 
    Int2,
    Int3,
    Int4,
    Bool
};

static uint32_t shaderDataTypeSize(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::Float:      return 4;
        case ShaderDataType::Float2:     return 4 * 2;
        case ShaderDataType::Float3:     return 4 * 3;
        case ShaderDataType::Float4:     return 4 * 4;
        case ShaderDataType::Mat3:       return 4 * 3 * 3;
        case ShaderDataType::Mat4:       return 4 * 4 * 4;
        case ShaderDataType::Int:        return 4;
        case ShaderDataType::Int2:       return 4 * 2;
        case ShaderDataType::Int3:       return 4 * 3;
        case ShaderDataType::Int4:       return 4 * 4;
        case ShaderDataType::Bool:       return 1;
    }

    return 0;
}

struct BufferElement
{
    std::string name;
    ShaderDataType type;
    uint32_t size;
    uint32_t offset;
    bool normalized;

    BufferElement(ShaderDataType pType, std::string const& pName, bool pNormalized = false)
    : name(pName), type(pType), size(shaderDataTypeSize(type)), offset(0), normalized(pNormalized)
    {}

    uint32_t getComponentCount() const
    {
        switch (type)
        {
            case ShaderDataType::Float:     return 1;
            case ShaderDataType::Float2:    return 2;
            case ShaderDataType::Float3:    return 3;
            case ShaderDataType::Float4:    return 4;
            case ShaderDataType::Int:       return 1;
            case ShaderDataType::Int2:      return 2;
            case ShaderDataType::Int3:      return 3;
            case ShaderDataType::Int4:      return 4;
            case ShaderDataType::Mat3:      return 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4;
            case ShaderDataType::Bool:      return 1;
        }
        return 0;
    }
};

class BufferLayout
{
public:
    BufferLayout() = default;
    BufferLayout(std::initializer_list<BufferElement> const& pElements) : elements(pElements)
    {
        calculateOffsetAndStride();
    }

    inline const std::vector<BufferElement>& getElements() const { return elements;}
    inline uint32_t getStride() const { return stride; }

    std::vector<BufferElement>::iterator begin() { return elements.begin(); }
    std::vector<BufferElement>::iterator end() { return elements.end(); }

private:
    std::vector<BufferElement> elements;
    uint32_t stride = 0;

    void calculateOffsetAndStride()
    {
        uint32_t offset = 0;
        stride = 0;
        for (auto& element : elements)
        {
            element.offset = offset;
            offset += element.size;
            stride += element.size;
        }
    }
};

class VertexBuffer
{
public:
    VertexBuffer(float * vertices, uint32_t size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
    void setLayout(BufferLayout const& layout);
    BufferLayout getLayout() const;

    static std::unique_ptr<VertexBuffer> create(float * vertices, uint32_t size);

private:
    uint32_t rendererId;
    BufferLayout layout;
};

class IndexBuffer
{
public:
    IndexBuffer(uint32_t * indices, uint32_t count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    static std::unique_ptr<IndexBuffer> create(uint32_t * indices, uint32_t count);
    uint32_t count() const;

private:
    uint32_t rendererId;
    uint32_t _count;;
};

} // namespace sc