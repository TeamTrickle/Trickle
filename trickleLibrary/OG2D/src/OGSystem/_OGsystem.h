#pragma once
//______________________________//
//|システムクラス１              |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//

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

#include <cmath>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <iostream>
#include <vector>
#include <map>

#define PI 3.1415926f

class Circle;
class Vec3;
class Vec2;
class Window;
class FPS;
class Mat4;
class Mat4x4;

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
class Vec2 {
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
class Window {
public:
	int _widht;
	int _height;
	char* _Name;
	bool _Screen;
	GLFWwindow *window;
public:
	Window();
	Window(int wi, int he, char* name, bool screen);
	~Window();
	void createWindow(int wi, int he, char* name, bool screen);
};
class FPS {
public:
	void Initialize();
	void Update();
private:
	float lastTime;
	int count;
	GLfloat fps;
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