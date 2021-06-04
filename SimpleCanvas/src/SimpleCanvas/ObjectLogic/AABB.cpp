#include "AABB.h"

#include <glad/glad.h>

#include "Camera/FPSCamera.h"

namespace sc
{
namespace
{
bool isInRange(float min, float value, float max)
{
    return min < value && value < max;
}
} // namespace

AABB::AABB(scmath::Vec3 const& min, scmath::Vec3 const& max)
{
    setMinMax(min, max);
}

void AABB::setMinMax(scmath::Vec3 const& min, scmath::Vec3 const& max) 
{
    _min = min;
    _max = max;

    if (!debugShader)
        debugShader = std::make_shared<Shader>(FileReader().readFile("assets/shaders/Debug_vertex.glsl"), FileReader().readFile("assets/shaders/Debug_fragment.glsl"));
}

void AABB::draw(FPSCamera const& camera, scmath::Mat4 const& modelMatrix) const
{
    std::vector<scmath::Vec3> const vertices
    {
        {_min.x, _max.y, _min.z},   // up
        {_min.x, _max.y, _max.z},
        {_max.x, _max.y, _max.z},
        {_max.x, _max.y, _max.z},
        {_max.x, _max.y, _min.z},
        {_min.x, _max.y, _min.z},

        {_min.x, _min.y, _max.z},   // front
        {_max.x, _min.y, _max.z},
        {_max.x, _max.y, _max.z},
        {_max.x, _max.y, _max.z},
        {_min.x, _max.y, _max.z},
        {_min.x, _min.y, _max.z},

        {_max.x, _min.y, _max.z},  // right
        {_max.x, _min.y, _min.z},
        {_max.x, _max.y, _min.z},
        {_max.x, _max.y, _min.z},
        {_max.x, _max.y, _max.z},
        {_max.x, _min.y, _max.z},

        {_min.x, _min.y, _min.z},   // left
        {_min.x, _min.y, _max.z},
        {_min.x, _max.y, _max.z},
        {_min.x, _max.y, _max.z},
        {_min.x, _max.y, _min.z},
        {_min.x, _min.y, _min.z},

        {_max.x, _min.y, _max.z},   // down
        {_min.x, _min.y, _max.z},
        {_min.x, _min.y, _min.z},
        {_min.x, _min.y, _min.z},
        {_max.x, _min.y, _min.z},
        {_max.x, _min.y, _max.z},

        {_max.x, _min.y, _min.z},   // back
        {_min.x, _min.y, _min.z},
        {_min.x, _max.y, _min.z},
        {_min.x, _max.y, _min.z},
        {_max.x, _max.y, _min.z},
        {_max.x, _min.y, _min.z}
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
    
    debugShader->uploadUniformMat4("u_ViewProjection", camera.getViewProjMatrix());
    debugShader->uploadUniformMat4("u_Model", modelMatrix);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP, 0, vertices.size());
    glBindVertexArray(0);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // for normal draw
}

bool AABB::isCollision(AABB const& other) const
{
    return (_min.x <= other._max.x && _max.x >= other._min.x) &&
           (_min.y <= other._max.y && _max.y >= other._min.y) &&
           (_min.z <= other._max.z && _max.z >= other._min.z);
}

scmath::Vec3 AABB::getVertexP(scmath::Vec3 const& normal) const
{
    scmath::Vec3 result(_min);
	if (normal.x >= 0)
		result.x = _max.x;
	if (normal.y >= 0)
		result.y = _max.y;
	if (normal.z >= 0)
		result.z = _max.z;
    return result;
}
} // namespace sc