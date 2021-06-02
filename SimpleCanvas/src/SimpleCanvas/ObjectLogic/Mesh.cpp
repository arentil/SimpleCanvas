#include "Mesh.h"

#include <glad/glad.h>

namespace sc
{
TextureMesh::TextureMesh(std::vector<TextureVertex> const& vertices, TexturePtr texturePtr)
: _vertices(vertices), _texturePtr(texturePtr)
{
    initialize();
}

void TextureMesh::draw(ShaderPtr shader, FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) const
{   
    //_aabb.draw(camera, modelMatrix);
    if (! camera._frustum.boxInFrustum(_aabb, modelMatrix))
    {
        return;
    }

    shader->bind();
    if (_texturePtr)
        _texturePtr->bind();

    shader->uploadUniformMat4("u_ViewProjection", camera.getViewProjMatrix());
    shader->uploadUniformMat4("u_Model", modelMatrix);
    shader->uploadUniformMat4("u_ModelInvT", scmath::Mat4::transpose(scmath::Mat4::inverse(modelMatrix)));
    shader->uploadUniformFloat("u_Ambient", lights.ambient);
    shader->uploadUniformFloat3("u_Diffuse", lights.diffuse);
    shader->uploadUniformFloat("u_Specular", lights.specular);
    shader->uploadUniformFloat3("u_ViewPos", camera.getPosition());

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

    // aabb bounding for frustrum clipping
    scmath::Vec3 minVertex = _vertices.front().position;
    scmath::Vec3 maxVertex = _vertices.front().position;
    for (auto const& vertex : _vertices)
    {
        minVertex.x = std::min(minVertex.x, vertex.position.x);
        minVertex.y = std::min(minVertex.y, vertex.position.y);
        minVertex.z = std::min(minVertex.z, vertex.position.z);

        maxVertex.x = std::max(maxVertex.x, vertex.position.x);
        maxVertex.y = std::max(maxVertex.y, vertex.position.y);
        maxVertex.z = std::max(maxVertex.z, vertex.position.z);
    }
    _aabb.setMinMax(minVertex, maxVertex);
}

ColorMesh::ColorMesh(std::vector<ColorVertex> const& vertices)
: _vertices(vertices)
{
    initialize();
}

void ColorMesh::draw(ShaderPtr shader, FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) const
{
    //_aabb.draw(camera, modelMatrix);
    if (! camera._frustum.boxInFrustum(_aabb, modelMatrix))
    {
        return;
    }

    shader->bind();
    // no texture binding since the plane color will be used

    shader->uploadUniformMat4("u_ViewProjection", camera.getViewProjMatrix());
    shader->uploadUniformMat4("u_Model", modelMatrix);
    shader->uploadUniformMat4("u_ModelInvT", scmath::Mat4::transpose(scmath::Mat4::inverse(modelMatrix)));
    shader->uploadUniformFloat("u_Ambient", lights.ambient);
    shader->uploadUniformFloat3("u_Diffuse", lights.diffuse);
    shader->uploadUniformFloat("u_Specular", lights.specular);
    shader->uploadUniformFloat3("u_ViewPos", camera.getPosition());

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


    // aabb bounding for frustrum clipping
    scmath::Vec3 minVertex = _vertices.front().position;
    scmath::Vec3 maxVertex = _vertices.front().position;
    for (auto const& vertex : _vertices)
    {
        minVertex.x = std::min(minVertex.x, vertex.position.x);
        minVertex.y = std::min(minVertex.y, vertex.position.y);
        minVertex.z = std::min(minVertex.z, vertex.position.z);

        maxVertex.x = std::max(maxVertex.x, vertex.position.x);
        maxVertex.y = std::max(maxVertex.y, vertex.position.y);
        maxVertex.z = std::max(maxVertex.z, vertex.position.z);
    }
    _aabb.setMinMax(minVertex, maxVertex);
}
} // namespace sc