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
	Circle(float, float, float);
	Circle(int, int, int);
	Circle(Circle&);
};
class Vec3 {
public:
	float x, y, z;
	Vec3();
	Vec3(float, float, float);
	Vec3(int, int, int);
};
class Vec2
{
public:
	float x, y;
	Vec2();
	Vec2(float, float);
	Vec2(int, int);
	//Vec2(Vec2&);
	void Normalize();
	float GetLength();

	Vec2 operator+(Vec2&);
	Vec2 operator-(Vec2&);
	Vec2 operator*(float);
	void operator+=(Vec2&);
	void operator*=(float);
	void operator-=(Vec2&);
};
class Mat4 {
public:
	float mat4[4];
	Mat4(float, float, float, float);
	Mat4(int, int, int, int);
};
class Mat4x4 {
public:
	float mat4[16];
	Mat4x4(float ex, float ey, float ez, float ew,
		float sx, float sy, float sz, float sw,
		float dx, float dy, float dz, float dw,
		float rx, float ry, float rz, float rw);
	Mat4x4(int ex, int ey, int ez, int ew,
		int sx, int sy, int sz, int sw,
		int dx, int dy, int dz, int dw,
		int rx, int ry, int rz, int rw);
};


class Box3D {
public:
	float x, y, z, w, h, d;
	Box3D();
	//座標とサイズ
	Box3D(float ex, float ey, float ez, float ew, float eh, float ed);
	Box3D(const Box3D &_e);
private:
	int IsOdd(int n, int a, int b);
	int InOdd(int n, int a, int b);
	int IfOdd(int n, int a, int b);
};
class Box2D {
public:
	float x, y, w, h;
	Box2D();
	Box2D(float x_, float y_, float w_, float h_);
	Box2D(int x_, int y_, int w_, int h_);
	Box2D(const Box2D& b_);
	Box2D(const Vec2& p, const Vec2& s);
	void Offset(float x_, float y_);
	void Offset(int x_, int y_);
	void OffsetSize();
	Box2D operator+(Box2D& b);
	Box2D operator-(Box2D& b);
	Box2D operator*(Box2D& b);
	void operator+=(Box2D& b);
	void operator-=(Box2D& b);
	void operator*=(Box2D& b);
};
class Color
{
public:
	float red, green, blue, alpha;
	Color();
	Color(const float r, const float g, const float b, const float a);
	Color(const int r, const int g, const int b, const int a);
	unsigned int Getcolor() const;
	void Color::operator+=(Color& b);
	void Color::operator*=(Color& b);
	void Color::operator-=(Color& b);
	void Color::operator=(Color& b);
};

namespace OG
{
	float ToRadian(const  float  degree_);
	void Cross(float*, float*, float*);
	float inner(Vec2&, Vec2&);
	float inner(float, float, float, float);
	float inner(int, int, int, int);
	float cross(Vec2&, Vec2&);
	float cross(float, float, float, float);
	float cross(int, int, int, int);
	float doubleinner(Vec2&);
	float doubleinner(float, float);
	float doubleinner(int, int);
	float get_distance(float, float, float, float, float, float);
}