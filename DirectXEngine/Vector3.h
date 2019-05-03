#ifndef  VECTOR3_H
#include <iostream>
class Vector3
{
public:
	float x;
	float y;
	float z;
public:
	//Constructor
	Vector3() :x(0), y(0), z(0) {
	}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3(float x) : x(x), y(x), z(x) {}


	Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
	~Vector3() {}

	//Operators
	Vector3 operator+(const Vector3& v) { return Vector3(this->x + v.x, this->y + v.y, this->z + v.z); }
	Vector3 operator-(const Vector3& v) { return Vector3(this->x - v.x, this->y - v.y, this->z - v.z); }
	Vector3 operator*(const float& v) { return Vector3(this->x * v, this->y * v, this->z *v); }
	Vector3 operator/(const float& v) { return Vector3(this->x / v, this->y / v, this->z / v); }
	Vector3 operator=(const Vector3 v) { this->x = v.x; this->y = v.y; this->z = v.z; return *this; }

	Vector3& operator+=(const Vector3& v) { this->x += v.x; this->y += v.y; this->z += v.z; return *this; }
	Vector3& operator*=(const float& v) { this->x *= v; this->y *= v; this->z *= v; return *this; }
	Vector3& operator/=(const float& v) { this->x /= v; this->y /= v;	this->z /= v; return *this; }
	float& operator[](std::size_t i) { return *((float*)this + 1); }

	//Functions
	Vector3 cross(const Vector3 & v) { return Vector3(this->y*v.z - this->z*v.y, this->z*v.x - this->x*v.z, this->x*v.y - this->y*v.x); }
	float magnitude() { return  std::sqrt((x*x) + (y*y) + (z*z)); }
	float dot(const Vector3& v) { return this->x * v.x + this->y * v.y + this->z *v.z; }
	void normalize() { float len = magnitude(); if (len != 0.) { x /= len; y /= len; z /= len; } }
	//Print [x,y,z]
	void print() { std::cout << "[" << x << "," << y << "," << z << "]" << std::endl; }

};

#define VECTOR3_H
#endif // ! VECTOR3_H