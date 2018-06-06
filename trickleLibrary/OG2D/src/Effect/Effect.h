#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Effect : public TaskObject , public GameObject
{
	class Animation
	{
	public:
		Easing easing_x;
		Easing easing_y;
		float time;
		Vec2 startPos;
		Vec2 endPos;
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
	Vec2 oneSize;
public:
	explicit Effect(const Vec2& pos, const Vec2& size, const Vec2& srcSize, const unsigned int number, const unsigned int time, const unsigned int onetime, const std::string& tag);
	virtual ~Effect();
	void UpDate();
	void Render2D();
	void Set(const Vec2& start_, const Vec2& end_,const float time_ = 10.f);
	void SetTexture(Texture*);
	typedef std::shared_ptr<Effect> SP;
	//位置、サイズ、元サイズ、枚数、表示時間、1枚あたりの時間
	static SP Create(const Vec2& pos, const Vec2& size, const Vec2& srcSize, const unsigned int number, const unsigned int time, const unsigned int onetime = 10, const std::string& tag = "", const bool = true);
};