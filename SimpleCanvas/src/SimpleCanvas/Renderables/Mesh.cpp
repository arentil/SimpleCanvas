#include "Mesh.h"

#include <glad/glad.h>

namespace sc
{
Mesh::Mesh(std::vector<Vertex> const& vertices, std::vector<uint32_t> const& indices, Texture2d const& texture)
: _vertices(vertices), _indices(indices), _texture(texture)
{
    initialize();
}

void Mesh::draw(Shader const& shader, Camera const& camera, scmath::Mat4 const& modelMatrix) const
{
    shader.bind();
    _texture.bind();
    
    shader.uploadUniformMat4("u_ViewProjection", camera.getViewProjMatrix());
    shader.uploadUniformMat4("u_Model", modelMatrix);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Mesh::initialize() 
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(uint32_t), _indices.data(), GL_STATIC_DRAW);

    // vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);  // nullptr change to (void*)0 if not work

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    glBindVertexArray(0);
}
} // namespace sc