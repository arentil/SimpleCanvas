#pragma once

#include "Plane.h"
#include "Renderables/AABB.h"

namespace sc
{
class Frustum
{
    enum { TOP = 0, BOTTOM, LEFT, RIGHT, NEAR, FAR };

public:
    Frustum() = default;

	void setCamInternals(float pangle, float pratio, float pnearD, float pfarD);
	void setCamDef(scmath::Vec3 &p, scmath::Vec3 &l, scmath::Vec3 &u);
	bool pointInFrustum(scmath::Vec3 const& point) const;
	bool sphereInFrustum(scmath::Vec3 const& point, float radius) const;
	// bool boxInFrustum(AABB const& b) const;

    Plane pl[6];
    scmath::Vec3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
    float nearD, farD, ratio, angle,tang;
	float nw,nh,fw,fh;
};
} // namespace sc