#pragma once

#include <SCMath.h>

namespace sc
{
struct TransformComponent
{
    scmath::Vec3 Translation = {0.0f, 0.0f, 0.0f};
    scmath::Vec3 Rotation = {0.0f, 0.0f, 0.0f};
    scmath::Vec3 Scale = {1.0f, 1.0f, 1.0f};

    scmath::Mat4 GetTransform() const
    {
        scmath::Mat4 rotation = scmath::Mat4::rotateX(Rotation.x)
            * scmath::Mat4::rotateY(Rotation.y)
            * scmath::Mat4::rotateZ(Rotation.z);
        
        return scmath::Mat4::translate(Translation)
            * rotation
            * scmath::Mat4::scale(Scale);
    }
};
} // namespace sc