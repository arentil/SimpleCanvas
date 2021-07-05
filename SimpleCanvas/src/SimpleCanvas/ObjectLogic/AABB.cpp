#include "AABB.h"

#include <glad/glad.h>

#include "Camera/CameraController.h"

namespace sc
{

AABB::AABB(scmath::Vec3 const& min, scmath::Vec3 const& max)
: bb(min, max)
{}

void AABB::initDebugShader() 
{
    if (!debugShader)
        debugShader = std::make_shared<Shader>(FileReader().readFile("assets/shaders/Debug_vertex.glsl"), FileReader().readFile("assets/shaders/Debug_fragment.glsl"));
}

void AABB::draw(CameraController const& camCtrl, scmath::Mat4 const& modelMatrix) const
{
    scmath::Vec3 const& min = bb.min;
    scmath::Vec3 const& max = bb.max;
    std::vector<scmath::Vec3> const vertices
    {
        {min.x, max.y, min.z},   // up
        {min.x, max.y, max.z},
        {max.x, max.y, max.z},
        {max.x, max.y, max.z},
        {max.x, max.y, min.z},
        {min.x, max.y, min.z},

        {min.x, min.y, max.z},   // front
        {max.x, min.y, max.z},
        {max.x, max.y, max.z},
        {max.x, max.y, max.z},
        {min.x, max.y, max.z},
        {min.x, min.y, max.z},

        {max.x, min.y, max.z},  // right
        {max.x, min.y, min.z},
        {max.x, max.y, min.z},
        {max.x, max.y, min.z},
        {max.x, max.y, max.z},
        {max.x, min.y, max.z},

        {min.x, min.y, min.z},   // left
        {min.x, min.y, max.z},
        {min.x, max.y, max.z},
        {min.x, max.y, max.z},
        {min.x, max.y, min.z},
        {min.x, min.y, min.z},

        {max.x, min.y, max.z},   // down
        {min.x, min.y, max.z},
        {min.x, min.y, min.z},
        {min.x, min.y, min.z},
        {max.x, min.y, min.z},
        {max.x, min.y, max.z},

        {max.x, min.y, min.z},   // back
        {min.x, min.y, min.z},
        {min.x, max.y, min.z},
        {min.x, max.y, min.z},
        {max.x, max.y, min.z},
        {max.x, min.y, min.z}
    };

    uint32_t VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(scmath::Vec3), vertices.data(), GL_STATIC_DRAW);

    // vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, sizeof(scmath::Vec3), nullptr);

    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // for wireframe draw
    debugShader->bind();
    
    debugShader->uploadUniformMat4("u_ViewProjection", camCtrl.getViewProj());
    debugShader->uploadUniformMat4("u_Model", modelMatrix);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP, 0, vertices.size());
    glBindVertexArray(0);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // for normal draw
}

std::pair<bool, CollisionSide> AABB::getCollision(AABB const& other) const
{
    if ((bb.min.x <= other.bb.max.x && bb.max.x >= other.bb.min.x) &&
        (bb.min.y <= other.bb.max.y && bb.max.y >= other.bb.min.y) &&
        (bb.min.z <= other.bb.max.z && bb.max.z >= other.bb.min.z))
        return std::make_pair(true, getCollisionSide(other));

    return std::make_pair(false, CollisionSide::UNDEFINED);
}

CollisionSide AABB::getCollisionSide(AABB const& other) const
{
    float precision = 0.15f;

    if (bb.max.y <= other.bb.min.y + precision)
        return CollisionSide::DOWN;
    if (bb.min.y >= other.bb.max.y - precision)
        return CollisionSide::UP;
    if (bb.max.x <= other.bb.min.x + precision)
        return CollisionSide::LEFT;
    if (bb.min.x >= other.bb.max.x - precision)
        return CollisionSide::RIGHT;
    if (bb.max.z <= other.bb.min.z + precision)
        return CollisionSide::FRONT;
    if (bb.min.z >= other.bb.max.z - precision)
        return CollisionSide::BACK;

    // undefined direction
    return CollisionSide::UNDEFINED;
}

CollisionSide AABB::getOpposideSide(CollisionSide side)
{
    return opposideDirectionMap.at(side);
}

scmath::Vec3 AABB::getVertexP(scmath::Vec3 const& normal) const
{
    scmath::Vec3 result(bb.min);
	if (normal.x >= 0)
		result.x = bb.max.x;
	if (normal.y >= 0)
		result.y = bb.max.y;
	if (normal.z >= 0)
		result.z = bb.max.z;
    return result;
}
} // namespace sc