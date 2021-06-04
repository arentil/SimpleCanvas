#include "Mesh.h"

#include <glad/glad.h>

namespace sc
{
namespace
{
std::vector<scmath::Vec3> aabb8Corners(AABB const& aabb)
{
    const float minX = aabb._min.x;
    const float minY = aabb._min.y;
    const float minZ = aabb._min.z;
    const float maxX = aabb._max.x;
    const float maxY = aabb._max.y;
    const float maxZ = aabb._max.z;

    return
    {
        aabb._max, // minX, minY, minZ
        aabb._min, // maxX, maxY, maxZ
        {minX, maxY, maxZ},
        {minX, maxY, minZ},
        {maxX, maxY, minZ},
        {maxX, minY, minZ},
        {maxX, minY, maxZ},
        {minX, minY, maxZ},
    };
}

AABB findNewAABB(AABB const& aabb, scmath::Mat4 const& modelMatrix)
{
    std::vector<scmath::Vec3> corners = aabb.corners;
    for (auto & corner : corners)
    {
        corner = modelMatrix * corner;
    }
        // aabb bounding for frustrum clipping
    scmath::Vec3 minVertex = corners.front();
    scmath::Vec3 maxVertex = corners.front();
    for (auto const& corner : corners)
    {
        minVertex.x = std::min(minVertex.x, corner.x);
        minVertex.y = std::min(minVertex.y, corner.y);
        minVertex.z = std::min(minVertex.z, corner.z);

        maxVertex.x = std::max(maxVertex.x, corner.x);
        maxVertex.y = std::max(maxVertex.y, corner.y);
        maxVertex.z = std::max(maxVertex.z, corner.z);
    }
    AABB result(minVertex, maxVertex);
    return result;
}
}

TextureMesh::TextureMesh(std::vector<TextureVertex> const& vertices, TexturePtr texturePtr)
: _vertices(vertices), _texturePtr(texturePtr)
{
    initialize();
}

void TextureMesh::draw(ShaderPtr shader, FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) const
{   
    AABB newAABB = findNewAABB(_aabb, modelMatrix);
    newAABB.draw(camera, scmath::Mat4::identity());
    //_aabb.draw(camera, modelMatrix);
    if (!camera.frustum.isAABBvisible(newAABB))
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
    _aabb.corners = aabb8Corners(_aabb);
}

ColorMesh::ColorMesh(std::vector<ColorVertex> const& vertices)
: _vertices(vertices)
{
    initialize();
}

void ColorMesh::draw(ShaderPtr shader, FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) const
{
    //_aabb.draw(camera, modelMatrix);
    if (! camera.frustum.isAABBvisible(_aabb))
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

CubemapMesh::CubemapMesh(std::vector<CubemapVertex> const& vertices, TexturePtr texturePtr) 
: _vertices(vertices), _texturePtr(texturePtr)
{
    initialize();
}
void CubemapMesh::draw(ShaderPtr shader, FPSCamera const& camera, Lights const& , scmath::Mat4 const& modelMatrix) const 
{
    shader->bind();
    if (_texturePtr)
        _texturePtr->bind();

    shader->uploadUniformMat4("u_ViewProjection", camera.getViewProjMatrix());
    shader->uploadUniformMat4("u_Model", modelMatrix);
    shader->uploadUniformMat4("u_ModelInvT", scmath::Mat4::transpose(scmath::Mat4::inverse(modelMatrix)));
    shader->uploadUniformFloat3("u_ViewPos", camera.getPosition());

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    glBindVertexArray(0);
}

void CubemapMesh::initialize()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(CubemapVertex), _vertices.data(), GL_STATIC_DRAW);

    // vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, sizeof(CubemapVertex), nullptr);

    // vertex texture coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(CubemapVertex), (void*)offsetof(CubemapVertex, texCoord));

    glBindVertexArray(0);
}
} // namespace sc