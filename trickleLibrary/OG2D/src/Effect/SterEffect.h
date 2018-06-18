//#pragma once
//#include "OGSystem\OGsystem.h"
//#include "OGSystem\_OGsystem.h"
//#include "Object\Object.h"
//class SterEffect : public  GameObject , public  TaskObject
//{
//public:
//	//ステート状態
//	enum State
//	{
//		NON,
//		Motion,
//	};
//private:
//	typedef std::shared_ptr<SterEffect> SP;
//
//	//画像関連
//	const Box2D Src = { 0,0,78,79 };
//	Texture image;
//	
//
//	//アニメーション
//	struct Animetion
//	{
//		State motion;
//		void StateChenge(State);
//	};
//	Animetion animetion;
//
//	//Update内
//	void MotionActive();
//	void Think();
//
//	//Easing関連
//	Easing easingX;
//	Easing easingY;
//	std::shared_ptr<GameObject> target;
//	std::shared_ptr<SterEffect> effect;
//	void ResetEasing(Easing&);
//	void MoveEasing();
//	bool isPlayed;
//
//	//タスク関連
//	std::string taskName;
//	void UpDate();
//	void Render2D();
//	bool Finalize();
//public:
//	SterEffect();
//	virtual ~SterEffect();
//	static SterEffect::SP Create(std::shared_ptr<GameObject>,bool = true);
//	//タイミングをずらす場合に使用する
//	static SterEffect::SP Create(std::shared_ptr<GameObject>, std::shared_ptr<SterEffect> Targeteffect ,bool = true);
//	bool Initialize(std::shared_ptr<GameObject>);
//	//タイミングをずらす場合に使用する
//	bool Initialize(std::shared_ptr<GameObject>, std::shared_ptr<SterEffect> Targeteffect);
//	///リザルト時・喜ぶモーションにするときに使用します。
//	bool EasingIsPlay();
//};