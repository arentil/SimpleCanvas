#include "Cube.h"

Cube::Cube(sc::Shader const& shader, sc::Camera const& camera, sc::Texture2d const& texture) 
: _shader(shader), _camera(camera)
{
    float vert[5 * 8] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, -1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -1.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, -1.0f, 0.0f, 1.0f
		};

    std::vector<sc::Vertex> vertices;
    vertices.reserve(8);
    for (size_t i = 0; i < 8; i++)
    {
        sc::Vertex vertex;
        vertex.position = scmath::Vec3(vert[i * 5], vert[i * 5 + 1], vert[i * 5 + 2]);
        vertex.texCoord = scmath::Vec2(vert[i * 5 + 3], vert[i * 5 + 4]);
        vertices.push_back(vertex);
    }

    std::vector<uint32_t> indices{	
        0, 1, 2, 2, 3, 0, // front
        6, 5, 4, 4, 7, 6, // back
        3, 2, 6, 6, 7, 3, // top
        0, 4, 5, 5, 1, 0, // bottom
        4, 0, 3, 3, 7, 4, // left
        1, 5, 6, 6, 2, 1 // right
    };

    std::vector<sc::Mesh> const meshes{{vertices, indices, texture}};
    _model = std::make_shared<sc::Model>(meshes);
}

void Cube::draw(scmath::Mat4 const& modelMatrix) const
{
    _model->draw(_shader, _camera, modelMatrix);
}