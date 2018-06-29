#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Effect : public TaskObject, public GameObject
{
	class Animation
	{
	public:
		Easing easing_x;
		Easing easing_y;
		float time;
		Vec2 startPos;
		Vec2 endPos;
		Vec2 preS;
		Vec2 preE;
		bool flag;
	};
public:
	enum Mode
	{
		Normal,
		Flash,
		Decrease,
		Expansion,
		WindR,
		WindL,
		Down,
	};
	enum ModeAlpha
	{
		NON,
		FLASH,
		DOWN,
		UP,
	};
private:
	Texture* image;
	Box2D draw;
	Box2D src;
	Animation anim;
	unsigned int animCnt;
	unsigned int num;
	unsigned int time;
	unsigned int one_time;
	float alpha;
	Vec2 oneSize;
	Color color;
	Mode mode;
	ModeAlpha modealpha;
	Vec2 maxSize;
	Vec2* move;
	float MaxFallSpeed;
	float FallSpeed;
	float FinSpeed;
	bool flag;
	float oneangle;
	float angle;
	int direction;
	void Friction();
public:
	explicit Effect(const Vec2& pos, const Vec2& size, const Vec2& srcSize, const unsigned int number, const unsigned int time, const unsigned int onetime, const std::string& tag);
	virtual ~Effect();
	void UpDate();
	void Render2D();
	void Set(const Vec2& start_, const Vec2& end_, const float time_ = 10.f);
	void SetWind(const Vec2&maxSize, const Vec2& start_, const Vec2& end_, const Mode& mode, const float time_ = 10.f);
	void SetTexture(Texture*);
	void Color_a(const float a);
	void SetMode(const Mode&);
	void SetMaxSize(const Vec2&);
	void SetMove(const Vec2&);
	void SetSpeed(float maxfall, float fall, float fin);
	void SetAlphaMode(const ModeAlpha& mode);
	void SetAngle(float, int = 1);
	typedef std::shared_ptr<Effect> SP;
	//位置、サイズ、元サイズ、枚数、表示時間、1枚あたりの時間
	static SP Create(const Vec2& pos, const Vec2& size, const Vec2& srcSize, const unsigned int number, const unsigned int time, const unsigned int onetime = 10, const std::string& tag = "", const bool = true);
};