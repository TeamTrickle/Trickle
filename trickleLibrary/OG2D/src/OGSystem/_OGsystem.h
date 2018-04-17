#pragma once
//______________________________//
//|システムクラス１              |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//

//#if !defined (DEBUG)
//// Degub版のみコンソールを表示する設定
//#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
//#endif

// Windows:GLEWをスタティックライブラリ形式で利用
#define GLEW_STATIC
// GLFWのヘッダ内で他のライブラリを取り込む	
#define GLFW_INCLUDE_GLEXT
#define GLFW_INCLUDE_GLU
#define GLM_FORCE_SWIZZLE

// いくつかの余計な警告を表示しないようにする
#pragma warning (disable:4244)
#pragma warning (disable:4522)
#pragma warning (disable:4800)
#pragma warning (disable:4996)

#pragma comment(lib, "OPENGL32.lib")
#pragma comment(lib, "GLU32.lib")
#pragma comment(lib, "Win64/OpenAL32.lib")

#if defined(_MSC_VER)
// Windows:外部ライブラリのリンク指定
#if defined (_DEBUG)
#pragma comment(lib, "glew32sd.lib")
#pragma comment(lib, "glfw3d.lib")
#else
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#endif
#endif

#if defined(_MSC_VER)
//EWを先にインクルードする必要がある。
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "al\al.h"
#include "al\alc.h"

#include <memory>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <iostream>
#include <vector>
#include <map>

#define PI 3.1415926f
typedef unsigned char u_char;
typedef unsigned int u_int;
typedef unsigned long u_long;

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
	float CenterX, CenterY, r;
	Circle()
		:r(0), CenterX(0), CenterY(0)
	{
	};
	Circle(float _x, float _y, float _r)
		:r(_r), CenterX(_x), CenterY(_y)
	{
	};
	Circle(int _x, int _y, int _r)
		:r((float)_r), CenterX((float)_x), CenterY((float)_y)
	{
	};
	Circle(Circle &_c)
		:r(_c.r), CenterX(_c.CenterX), CenterY(_c.CenterY)
	{
	};
};
class Vec3 {
public:
	float x, y, z;
	Vec3()
		:x(0), y(0), z(0)
	{}
	Vec3(float ex, float ey, float ez)
		:x(ex), y(ey), z(ez)
	{
	}
	Vec3(int ex, int ey, int ez)
		:x((float)ex), y((float)ey), z((float)ez)
	{
	}
};
class Vec2 
{
public:
	float x, y;
	Vec2()
		:x(0), y(0)
	{
	}
	Vec2(float ex, float ey)
		:x(ex), y(ey)
	{
	}
	Vec2(int ex, int ey)
		:x((float)ex), y((float)ey)
	{
	}
	void Normalize();
	float GetLength();

	Vec2 Vec2::operator+(Vec2 v) { return Vec2(x + v.x, y + v.y); }
	Vec2 Vec2::operator-(Vec2 v) { return Vec2(x - v.x, y - v.y); }
	Vec2 Vec2::operator*(float n) { return Vec2(x*n, y*n); }
	void Vec2::operator+=(Vec2 v) { x += v.x; y += v.y; }
	void Vec2::operator*=(float n) { x *= n; y *= n; }
	void Vec2::operator-=(Vec2 v) { x -= v.x; y -= v.y; }
};
class Mat4 {
public:
	float mat4[4];
	Mat4(float ex, float ey, float ez, float ew) {
		mat4[0] = ex;
		mat4[1] = ey;
		mat4[2] = ez;
		mat4[3] = ew;
	}
};
class Mat4x4 {
public:
	float mat4[16];
	Mat4x4(float ex, float ey, float ez, float ew,
		float sx, float sy, float sz, float sw,
		float dx, float dy, float dz, float dw,
		float rx, float ry, float rz, float rw) {
		mat4[0] = ex;
		mat4[1] = ey;
		mat4[2] = ez;
		mat4[3] = ew;
		mat4[4] = sx;
		mat4[5] = sy;
		mat4[6] = sz;
		mat4[7] = sw;
		mat4[8] = dx;
		mat4[9] = dy;
		mat4[10] = dz;
		mat4[11] = dw;
		mat4[12] = rx;
		mat4[13] = ry;
		mat4[14] = rz;
		mat4[15] = rw;
	}
};


class Box3D {
public:
	float x, y, z, w, h, d;
	Box3D()
		:x(0), y(0), z(0), w(0), h(0), d(0)
	{
	}
	//座標とサイズ
	Box3D(float ex, float ey, float ez, float ew, float eh, float ed)
		:x(ex), y(ey), z(ez), w(ew), h(eh), d(ed)
	{
	}
	Box3D(const Box3D &_e)
		:x(_e.x), y(_e.y), z(_e.z), w(_e.w), h(_e.h), d(_e.d)
	{
	}
	void LinesDraw(Box3D &b);
private:
	int IsOdd(int n, int a, int b);
	int InOdd(int n, int a, int b);
	int IfOdd(int n, int a, int b);
};
class Box2D {
public:
	float x, y, w, h;
	Box2D()
		:x(0), y(0), w(0), h(0)
	{
	}

	Box2D(float x_, float y_, float w_, float h_)
		:x(x_), y(y_), w(w_), h(h_)
	{
	}

	Box2D(int x_, int y_, int w_, int h_)
		:x((float)x_), y((float)y_), w((float)w_), h((float)h_)
	{
	}

	Box2D(const Box2D& b_)
		:x(b_.x), y(b_.y), w(b_.w), h(b_.h)
	{
	}
	Box2D(const Vec2 p, const Vec2 s)
		:x(p.x), y(p.y), w(s.x), h(s.y)
	{
	}
	bool Hit(const  Box2D& b_) const
	{
		if (x < b_.w	&&
			b_.x < w	&&
			y <b_.h	&&
			b_.y < h) {
			return true;
		}
		return false;
	}
	void Offset(float x_, float y_)
	{
		x += x_;
		y += y_;
	}
	void Offset(int x_, int y_)
	{
		x += (float)x_;
		y += (float)y_;
	}
	void OffsetSize()
	{
		this->w = this->w + this->x;
		this->h = this->h + this->y;
	}
	Box2D operator+=(Box2D b) { x += b.x; y += b.y; w += b.w; h += b.h; }
	Box2D operator-=(Box2D b) { x -= b.x; y -= b.y; w -= b.w; h -= b.h; }
};
namespace OG {
	float ToRadian(const  float  degree_);
	void MulitMatrixf(GLfloat*src1, GLfloat*src2, GLfloat*dst);
	void Normalize(GLfloat *v);
	void Cross(float* src1, float* src2, float* dst);
	float inner(Vec2 _v1, Vec2 _v2);
	float inner(float _x1, float _y1, float _x2, float _y2);
	float inner(int _x1, int _y1, int _x2, int _y2);
	float cross(Vec2 _v1, Vec2 _v2);
	float cross(float _x1, float _y1, float _x2, float _y2);
	float cross(int _x1, int _y1, int _x2, int _y2);
	float doubleinner(Vec2 _v);
	float doubleinner(float _x, float _y);
	float doubleinner(int _x, int _y);
	float get_distance(float x, float y, float x1, float y1, float x2, float y2);
	void _Rotate(float _angle, Vec2 _b[4]);
	void LineHitDraw(Vec2 _b[4]);
}
class Color
{
public:
	float red, green, blue, alpha;
	Color()
		:red(0.f), green(0.f), blue(0.f), alpha(0.f)
	{}
	Color(const float r, const float g, const float b, const float a)
		:red(r), green(g), blue(b), alpha(a)
	{}
	Color(const int r, const int g, const int b, const int a)
		:red((float)r), green((float)g), blue((float)b), alpha((float)a)
	{}
	unsigned int Getcolor() const;
	void Color::operator+=(Color b) { red += b.red; green += b.green; blue += b.blue; alpha += b.alpha; }
	void Color::operator*=(Color b) { red *= b.red; green *= b.green; blue *= b.blue; alpha *= b.alpha; }
	void Color::operator-=(Color b) { red -= b.red; green -= b.green; blue -= b.blue; alpha -= b.alpha; }
	void Color::operator=(Color b) { red = b.red; green = b.green; blue = b.blue; alpha = b.alpha; }
};