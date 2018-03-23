#pragma once
//______________________________//
//|システムクラス２              |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//
#include "OGSystem\_OGsystem.h"
#include "stb_image.h"

class Box3D;
class Box2D;
class CollisionCircle;
class CollisionBox;
class KeyInput;
class Texture;

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
};
class CollisionBox
{
public:
	Box2D hitBase;
	bool hitBox(CollisionBox b);
	bool hitCircle(CollisionCircle b);
	void Rotate(float _angle);
	float angle;
private:
	void hitdraw();
};
class CollisionCircle
{
public:
	Circle hitBase;
	bool hitBox(CollisionBox b);
	bool hitCircle(CollisionCircle b);
private:
};
class KeyInput{
public:
	KeyInput();
	bool KeyInputUp(GLFWwindow *w, int key);
	bool KeyInputDown(GLFWwindow *w, int key);
	bool KeyInputOn(GLFWwindow *w, int key);
private:
	int KeyInputOnTime[256];
	int KeyInputDownTime[256];
	int KeyInputUpTime[256];
	int Key[256];
};
class Texture {
public:
	Texture();
	~Texture();
	void TextureCreate(std::string _path);
	void Draw(Box2D draw, Box2D src);
	void Finalize();
	void Rotate(float radian);
	float angle;
private:
	GLuint _TexId;
	int TextureID;
	Box2D TexPos;
	Box2D Double;
	Vec2 TextureSize;
	GLfloat rotate[16];
	Vec2 _materix[4];
	const std::string FileName = "./data/image/";
	void _Rotate(float radian, GLfloat *mate);
};

namespace Key {
	static GLFWwindow *nowWindow;
	extern void Initialize(GLFWwindow *w);
	extern bool KeyInputUp(int key);
	extern bool KeyInputDown(int key);
	extern bool KeyInputOn(int key);
	extern void Finalize();
	static int KeyInputOnTime[256];
	static int KeyInputDownTime[256];
	static int KeyInputUpTime[256];
	/*static enum 
	{
		GPAD_BUTTON_A,
		GPAD_BUTTON_B,
		GPAD_BUTTON_X,
		GPAD_BUTTON_Y,
		GPAD_BUTTON_L,
		GPAD_BUTTON_R,
		GPAD_BUTTON_U,
		GPAD_BUTTON_D,
		GPAD_BUTTON_L1,
		GPAD_BUTTON_R1,
		GPAD_BUTTON_L2,
		GPAD_BUTTON_R2,

		GPAD_STIC_R,
		GPAD_STIC_L,
	};*/
}