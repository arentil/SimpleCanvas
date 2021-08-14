#pragma once

#include "Plane.h"
#include "ObjectLogic/AABB.h"
namespace sc
{
class Frustum
{
    enum { TOP = 0, BOTTOM, LEFT, RIGHT, NEAR, FAR };

public:
    Frustum() = default;

	void setCamInternals(float pangle, float pratio, float pnearD, float pfarD);
	void setCamDef(scmath::Vec3 const& eye, scmath::Vec3 const& target, scmath::Vec3 const& up);
	bool pointInFrustum(scmath::Vec3 const& point) const;
	bool sphereInFrustum(scmath::Vec3 const& point, float radius) const;
	bool isAABBvisible(AABB const& aabb) const;

    Plane planes[6];
    scmath::Vec3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
    float nearD, farD, ratio, angle,tang;
	float nw,nh,fw,fh;
};
} // namespace sc