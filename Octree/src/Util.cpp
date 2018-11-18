
// Kevin M.Smith - CS 134 SJSU

#include "Util.h"




//---------------------------------------------------------------
// test if a ray intersects a plane.  If there is an intersection, 
// return true and put point of intersection in "point"
//
bool rayIntersectPlane(const ofVec3f &rayPoint, const ofVec3f &raydir, const ofVec3f &planePoint,
	const ofVec3f &planeNorm, ofVec3f &point)
{
	// if d1 is 0, then the ray is on the plane or there is no intersection
	//
	const float eps = .000000001;
	float d1 = (planePoint - rayPoint).dot(planeNorm);
	if (abs(d1) < eps) return false;

	//  if d2 is 0, then the ray is parallel to the plane
	//
	float d2 = raydir.dot(planeNorm);
	if (abs(d2) < eps) return false;

	//  compute the intersection point and return it in "point"
	//
	point = (d1 / d2) * raydir + rayPoint;
	return true;
}

// Compute the reflection of a vector incident on a surface at the normal.
// 
//
ofVec3f reflectVector(const ofVec3f &v, const ofVec3f &n) {
	return (v - 2 * v.dot(n) * n);
}