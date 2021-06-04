#include "Frustum.h"

namespace sc
{
#define ANG2RAD 3.14159265358979323846/180.0

void Frustum::setCamInternals(float pangle, float pratio, float pnearD, float pfarD) 
{
	ratio = pratio;
	angle = pangle;
	nearD = pnearD;
	farD = pfarD;

	tang = (float)tan(ANG2RAD * angle * 0.5) ;
	nh = nearD * tang;
	nw = nh * ratio;
	fh = farD  * tang;
	fw = fh * ratio;
}

void Frustum::setCamDef(scmath::Vec3 const& eye, scmath::Vec3 const& target, scmath::Vec3 const& up)
{
    scmath::Vec3 nc,fc,X,Y,Z;

	// compute the Z axis of camera
	// this axis points in the opposite direction from
	// the looking direction
	Z = (eye - target).normalized();

	// X axis of camera with given "up" vector and Z axis
	X = up.cross(Z).normalized();

	// the real "up" vector is the cross product of Z and X
	Y = Z.cross(X);

	// compute the centers of the near and far planes
	nc = eye - Z * nearD;
	fc = eye - Z * farD;

	// compute the 4 corners of the frustum on the near plane
	ntl = nc + Y * nh - X * nw;
	ntr = nc + Y * nh + X * nw;
	nbl = nc - Y * nh - X * nw;
	nbr = nc - Y * nh + X * nw;

	// compute the 4 corners of the frustum on the far plane
	ftl = fc + Y * fh - X * fw;
	ftr = fc + Y * fh + X * fw;
	fbl = fc - Y * fh - X * fw;
	fbr = fc - Y * fh + X * fw;

	// compute the six planes
	// the function set3Points assumes that the points
	// are given in counter clockwise order
	pl[TOP].setPoints(ntr,ntl,ftl);
	pl[BOTTOM].setPoints(nbl,nbr,fbr);
	pl[LEFT].setPoints(ntl,nbl,fbl);
	pl[RIGHT].setPoints(nbr,ntr,fbr);
	pl[NEAR].setPoints(ntl,ntr,nbr);
	pl[FAR].setPoints(ftr,ftl,fbl);
}

bool Frustum::pointInFrustum(scmath::Vec3 const& point) const
{
    for(int i=0; i < 6; i++) 
    {
		if (pl[i].distance(point) < 0.0f)
			return false;
	}
	return true;
}

bool Frustum::sphereInFrustum(scmath::Vec3 const& point, float radius) const
{
	for(int i=0; i < 6; i++) 
    {
		if (pl[i].distance(point) < -radius)
			return false;
	}
	return true;
}

bool Frustum::boxInFrustum(AABB const& b, scmath::Mat4 const& modelMatrix) const
{
	for(int i=0; i < 6; i++)
    {
		if (pl[i].distance(modelMatrix * b.getVertexP(pl[i].normal)) < 0.0f)	// 0.0f ?
			return false;
	}
	return true;
}
} // namespace sc