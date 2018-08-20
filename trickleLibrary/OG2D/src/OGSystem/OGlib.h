///äeå^class
#pragma once
#include <cmath>
#define PI 3.1415926f

class Circle;
class Vec3;
class Vec2;
class Mat4;
class Mat4x4;
class Box3D;
class Box2D;
class Color;

class Circle
{
public:
	float center_x, center_y, r;
	Circle();
	Circle(const float, const float, const float);
	Circle(const int, const int, const int);
	Circle(const Circle&);
};
class Vec3 {
public:
	float x, y, z;
	Vec3();
	Vec3(const float, const float, const float);
	Vec3(const int, const int, const int);
};
class Vec2
{
public:
	float x, y;
	Vec2();
	Vec2(const float, const float);
	Vec2(const int, const int);
	void Normalize();
	float GetLength();

	Vec2 operator+(const Vec2&);
	Vec2 operator-(const Vec2&);
	Vec2 operator*(const float);
	void operator+=(const Vec2&);
	void operator*=(const float);
	void operator-=(const Vec2&);
	bool operator==(const Vec2&);
};
class Mat4 {
public:
	float mat4[4];
	Mat4(const float, const float, const float, const float);
	Mat4(const int, const int, const int, const int);
};
class Mat4x4 {
public:
	float mat4[16];
	Mat4x4(const float ex, const float ey, const float ez, const float ew,
		const float sx, const float sy, const float sz, const float sw,
		const float dx, const float dy, const float dz, const float dw,
		const float rx, const float ry, const float rz, const float rw);
	Mat4x4(const int ex, const int ey, const int ez, const int ew,
		const int sx, const int sy, const int sz, const int sw,
		const int dx, const int dy, const int dz, const int dw,
		const int rx, const int ry, const int rz, const int rw);
};


class Box3D {
public:
	float x, y, z, w, h, d;
	Box3D();
	Box3D(const float ex, const float ey, const float ez, const float ew, const float eh, const float ed);
	Box3D(const Box3D &_e);
private:
	int IsOdd(const int n, const int a, const int b);
	int InOdd(const int n, const int a, const int b);
	int IfOdd(const int n, const int a, const int b);
};
class Box2D {
public:
	float x, y, w, h;
	Box2D();
	Box2D(const float x_, const float y_, const float w_, const float h_);
	Box2D(const int x_, const int y_, const int w_, const int h_);
	Box2D(const Box2D& b_);
	Box2D(const Vec2& p, const Vec2& s);
	void Offset(const float x_, const float y_);
	void Offset(const int x_, const int y_);
	void OffsetSize();
	Box2D operator+(const Box2D& b);
	Box2D operator-(const Box2D& b);
	Box2D operator*(const Box2D& b);
	void operator+=(const Box2D& b);
	void operator-=(const Box2D& b);
	void operator*=(const Box2D& b);
};
class Color
{
public:
	float red, green, blue, alpha;
	Color();
	Color(const float r, const float g, const float b, const float a);
	Color(const int r, const int g, const int b, const int a);
	unsigned int Getcolor() const;
	void operator+=(const Color& b);
	void operator*=(const Color& b);
	void operator-=(const Color& b);
	Color operator+(const Color&);
	Color operator-(const Color&);
	Color operator*(const Color&);
};

namespace OG
{
	float ToRadian(const  float  degree_);
	void Cross(float*, float*, float*);
	float inner(const Vec2&, const Vec2&);
	float inner(const float, const float, const float, const float);
	float inner(const int, const int, const int, const int);
	float cross(const Vec2&, const Vec2&);
	float cross(const float, const float, const float, const float);
	float cross(const int, const int, const int, const int);
	float doubleinner(const Vec2&);
	float doubleinner(const float, const float);
	float doubleinner(const int, const int);
	float get_distance(const float, const float, const float, const float, const float, const float);
}