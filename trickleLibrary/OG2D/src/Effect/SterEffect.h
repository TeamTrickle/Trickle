#pragma once
#include "OGSystem\OGsystem.h"
#include "OGSystem\_OGsystem.h"
#include "Object\Object.h"
class SterEffect : public  GameObject , public  TaskObject
{
public:
	//ステート状態
	enum State
	{
		NON,
		Motion,
	};
private:
	typedef std::shared_ptr<SterEffect> SP;

	//画像関連
	const Box2D Src = { 0,0,322,322 };
	Texture image;
	

	//アニメーション
	struct Animetion
	{
		State motion;
		void StateChenge(State);
	};
	Animetion animetion;

	//Update内
	void MotionActive();
	void Think();

	//Easing関連
	Easing easingX;
	Easing easingY;
	std::shared_ptr<GameObject> target;
	void ResetEasing(Easing&);
	void MoveEasing();
	bool isPlay;

	//タスク関連
	std::string taskName;
	void UpDate();
	void Render2D();
	bool Finalize();
public:
	SterEffect();
	virtual ~SterEffect();
	static SterEffect::SP Create(std::shared_ptr<GameObject>,bool = true);
	bool Initialize(std::shared_ptr<GameObject>);

	bool EasingIsPleyed();
};