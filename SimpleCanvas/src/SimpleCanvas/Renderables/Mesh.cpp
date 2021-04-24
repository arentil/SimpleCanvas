#include "Mesh.h"

#include <glad/glad.h>

namespace sc
{
TextureMesh::TextureMesh(std::vector<TextureVertex> const& vertices, TexturePtr const texturePtr)
: _vertices(vertices), _texturePtr(texturePtr)
{
    initialize();
}

void TextureMesh::draw(Shader const& shader, Camera const& camera, Material const& material, scmath::Mat4 const& modelMatrix) const
{
    shader.bind();
    if (_texturePtr)
        _texturePtr->bind();

    shader.uploadUniformMat4("u_ViewProjection", camera.getViewProjMatrix());
    shader.uploadUniformMat4("u_Model", modelMatrix);
    shader.uploadUniformMat4("u_ModelInvT", scmath::Mat4::transpose(scmath::Mat4::inverse(modelMatrix)));
    shader.uploadUniformFloat("u_Ambient", material.ambient);
    shader.uploadUniformFloat3("u_Diffuse", material.diffuse);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    glBindVertexArray(0);
}

void TextureMesh::initialize() 
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(TextureVertex), _vertices.data(), GL_STATIC_DRAW);

    // vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), nullptr);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)offsetof(TextureVertex, normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)offsetof(TextureVertex, texCoord));

    glBindVertexArray(0);
}

ColorMesh::ColorMesh(std::vector<ColorVertex> const& vertices)
: _vertices(vertices)
{
    initialize();
}

void ColorMesh::draw(Shader const& shader, Camera const& camera, Material const& material, scmath::Mat4 const& modelMatrix) const
{
    shader.bind();
    // no texture binding since the plane color will be used

    shader.uploadUniformMat4("u_ViewProjection", camera.getViewProjMatrix());
    shader.uploadUniformMat4("u_Model", modelMatrix);
    shader.uploadUniformMat4("u_ModelInvT", scmath::Mat4::transpose(scmath::Mat4::inverse(modelMatrix)));
    shader.uploadUniformFloat("u_Ambient", material.ambient);
    shader.uploadUniformFloat3("u_Diffuse", material.diffuse);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    glBindVertexArray(0);
}

void ColorMesh::initialize() 
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(ColorVertex), _vertices.data(), GL_STATIC_DRAW);

    // vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), nullptr);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)offsetof(ColorVertex, normal));

    // vertex color
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)offsetof(ColorVertex, color));

    glBindVertexArray(0);
}
} // namespace sc