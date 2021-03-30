#include "Mesh.h"

#include <glad/glad.h>

namespace sc
{
Mesh::Mesh(std::vector<Vertex> const& vertices, std::shared_ptr<Texture2d> texturePtr)
: _vertices(vertices), _texturePtr(texturePtr)
{
    initialize();
}

void Mesh::draw(Shader const& shader, Camera const& camera, scmath::Mat4 const& modelMatrix) const
{
    shader.bind();
    if (_texturePtr)
        _texturePtr->bind();
    
    shader.uploadUniformMat4("u_ViewProjection", camera.getViewProjMatrix());
    shader.uploadUniformMat4("u_Model", modelMatrix);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    glBindVertexArray(0);
}

void Mesh::initialize() 
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW);

    // vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    glBindVertexArray(0);
}
} // namespace sc