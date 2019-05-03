#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <ostream>
#include <iostream> 
#include "Vector3.h"
using namespace std;
typedef Vector3 Point;

struct Sphere
{
	Vector3 position;
	float radius;

	Sphere() : radius(1.f) { }
	Sphere(Vector3& p, float r) :
		position(p), radius(r) { }
}
typedef Sphere;
struct AABB {
	Vector3 position;
	Vector3 size; // HALF SIZE!

	AABB() : size(1, 1, 1) { }
	AABB(const Vector3& p, const Vector3& s) :
		position(p), size(s) { }
}
typedef AABB;

struct Plane {
	Vector3 normal;
	float distance;

	inline Plane() : normal(1, 0, 0) { }
	inline Plane(const Vector3& n, float d) :
		normal(n), distance(d) { }
}
typedef Plane;
//
//float Classify(const AABB& aabb, const Plane& plane) {
//	// maximum extent in direction of plane normal 
//	float r = fabsf(aabb.size.x * plane.normal.x)
//		+ fabsf(aabb.size.y * plane.normal.y)
//		+ fabsf(aabb.size.z * plane.normal.z);
//
//	// signed distance between box center and plane //float d = plane.Test(mCenter);
//	float d = 2;// = Dot(plane.normal, aabb.position) + plane.distance;
//
//	// return signed distance
//	if (fabsf(d) < r) {
//		return 0.0f;
//	}
//	else if (d < 0.0f) {
//		return d + r;
//	}
//	return d - r;
//}
//bool Intersects(const Plane& f, const AABB& aabb) {
//	for (int i = 0; i < 6; ++i) {
//		float side = Classify(aabb, f);
//		if (side < 0) {
//			return false;
//		}
//	}
//	return true;
//}


std::ostream& operator<<(std::ostream& os, const Sphere& shape);


#endif // !GEOMETRY_H