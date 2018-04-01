#pragma once
//______________________________//
//|システムクラス２              |//
//|履歴：2018/03/20金子翔       |//
//|履歴：2018/03/23金子翔		   |//
//|____________________________|//
#include "OGSystem\_OGsystem.h"
#include "stb_image.h"

class Box3D;
class Box2D;
class CollisionCircle;
class CollisionBox;
class Texture;
class Camera2D;
class Input;
class EngineSystem;

class Input {
public:
	//enum
	enum in{
		B1,
		B2,
		B3,
		B4,
		CD,
		CU,
		CR,
		CL,
		L1,
		R1,
		D1,
		D2,
		SR,
		SL,
	};
	//class
	class GamePad
	{
	public:
		enum Pad
		{
			//仮装コントローラの入力設定
			BUTTON_A,		//1
			BUTTON_B,		//2
			BUTTON_X,		//3
			BUTTON_Y,		//4
			BUTTON_L1,		//5
			BUTTON_R1,		//6
			BUTTON_BACK,	//7
			BUTTON_START,	//8
			BUTTON_L3,		//9
			BUTTON_R3,		//10
			BUTTON_U,		//11
			BUTTON_R,		//12
			BUTTON_D,		//13
			BUTTON_L,		//14
		};
		enum AXIS {
			AXIS_LEFT_X,		//左スティックX値
			AXIS_LEFT_Y,		//左スティックY値
			AXIS_RIGHT_X,		//右スティックX値
			AXIS_RIGHT_Y,		//右スティックY値
			AXIS_BUTTON_NUM,
		};
		explicit GamePad(const int id);
		bool on(const int index);
		bool down(const int index);
		bool up(const int index);
		float axis(const int index);
		void upDate();
		void Initialize();
		void Reset();
		bool isPresent() const;
	private:
		bool registAxisButton(const int x_index, const int y_index, const float axis_threshold_);
		int id_;
		int button_num;
		int axis_num;
		int GPadData[14];
		std::vector<float> axis_value;
		bool axis_button;
		float axis_threshold;
		int axis_x_index;
		int axis_y_index;
		std::vector<u_char> button_on;
		std::vector<u_char> button_down;
		std::vector<u_char> button_up;
		std::vector<u_char> axis_button_on;
		std::vector<u_char> axis_button_down;
		std::vector<u_char> axis_button_up;
		int buttons() const;
		int axes() const;
	};
	class KeyBoard
	{
	public:
		enum Key
		{
			//キーボードの仮装キー設定
			A,S,D,W,Q,E,Z,X,C,R,F,V,T,
			G,B,Y,H,N,U,J,M,I,K,O,L,P,
			SPACE,ENTER, ESCAPE,
			UP,DOWN,LEFT,RIGHT,
		};
		KeyBoard();
		bool up(const int index);
		bool down(const int index);
		bool on(const int index);
		void upDate();
		GLFWwindow* nowWindow;
		bool isPresent;
		std::vector<u_char> button_on;
		std::vector<u_char> button_down;
		std::vector<u_char> button_up;
	private:
		int KeyData[256];
	};
	struct InputData
	{
		int button;		//ゲームパッドのボタン
		int key;		//キーボードのキー
	};
	//class宣言
	std::vector<GamePad> gamepad;
	KeyBoard keyboard;
	//変数
	bool Pad_Connection;
	//関数
	void Inputinit();
	bool on(in in_,int padNum);
	bool down(in in_,int padNum);
	bool up(in in_,int padNum);
	void upDate();
private:
	void ResetInputData();
	int inputData[256];
	std::vector<Input::GamePad> initGamePad();
	KeyBoard initkeyBoard(GLFWwindow *w);
	InputData inputdata[14];
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
class Camera2D
{
public:
	Camera2D()
	{}
	Camera2D(Box2D pos);
	~Camera2D();
	void Initialize(Box2D pos);
	void CameraUpDate();
	void Move(Vec2 est);
	void SetPos(Vec2 est);
	Vec2 GetPos();
	Vec2 position;
	typedef std::shared_ptr<Camera2D> SP;
	static SP Create(Box2D pos);
	int width;
	int height;
private:
	Box2D cameraPos;
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
class EngineSystem
{
public:
	EngineSystem();
	EngineSystem(int widht, int height, char* name, bool screen);
	Camera2D::SP camera;
	Window::SP window;
	Input input;
	void Initialize();
	void UpDate();
	void SetWindow(int width, int height, char* name, bool screen);
	bool DebugFunction;
private:
	int w_wi;
	int w_he;
	char* w_na;
	bool w_sc;
};
extern EngineSystem* gameEngine;