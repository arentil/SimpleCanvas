#include "BaseMesh.h"

namespace sc
{
BaseMesh::BaseMesh(size_t numberOfVertices)
: verticesCount(numberOfVertices)
{}

BaseMesh::BaseMesh(BaseMesh const& other)
: bb(other.bb), aabb(other.aabb), VAO(other.VAO), verticesCount(other.verticesCount)
{}

void BaseMesh::updateAABB(scmath::Mat4 const& modelMatrix) 
{
    scmath::Vec3 min = scmath::Vec3::Max();
    scmath::Vec3 max = scmath::Vec3::Min();
    for (auto const& corner : bb.get8Corners())
    {
        auto modelCorner = modelMatrix * corner;
        min.x = std::min(min.x, modelCorner.x);
        min.y = std::min(min.y, modelCorner.y);
        min.z = std::min(min.z, modelCorner.z);

        max.x = std::max(max.x, modelCorner.x);
        max.y = std::max(max.y, modelCorner.y);
        max.z = std::max(max.z, modelCorner.z);

    }
    aabb.bb.min = min;
    aabb.bb.max = max;
}
} // namespace sc