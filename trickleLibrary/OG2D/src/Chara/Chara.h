#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Chara : public GameObject, public TaskObject
{
public:
	enum Direction						//向きを管理
	{
		LEFT,
		RIGHT,
	};
private:
	Texture Image;
	Vec2 move;
	const float MOVE_SPEED;								//移動スピード
	const float JUMP_POWER;								//ジャンプパワー
	const float MAX_FALL;								//落下最大速度
	const float GRAVITY;		//重力加速度
	const float FIN_SPEED;								//摩擦
	Direction direction;										//向きを格納する変数
	std::string taskName;										//名
<<<<<<< HEAD
	int AnimCnt;
	bool isAuto;
	bool isCollision;
	int MoveCnt;
	__int8 isCollisionNow;
	bool isAutoOff;
=======
	int AnimCnt;			//アニメーションカウント
	bool isAuto;			//オート状態有無
	bool isCollision;		//当たり判定有無
	int MoveCnt;			//移動カウント
	__int8 isCollisionNow;	//当たり判定状態カウント
	bool isAutoOff;			//オートモード移行有無
	bool isAutoMode;		//オートモードでの移動指定有無
	Vec2 startPos;			//オートモード時の開始地点
	Vec2 EndPos;			//オートモード時の終了地点
	Easing easing_x;		//イージング移動値
>>>>>>> develop
public:
	Chara(std::string&, Vec2&);
	virtual ~Chara();
	typedef std::shared_ptr<Chara> SP;
	static SP Create(std::string&, Vec2&, bool = true);
	void UpDate();
	void Render2D();
	void Friction(Vec2&);
	void MoveCheck(Vec2);
	bool FootCheck();
	bool Jump();
	void AutoMove();
	void ManualMove(Vec2&);
	void IsCollisionCheck();
	bool CollisionNumCheck(__int8);
	void MoveReset();
	void SetDirection(const Direction&);
	void SetAutoFlag(const bool);
<<<<<<< HEAD
	Vec2 GetMove() const;
=======
	void SetAutoMode(const bool);
	Vec2 GetMove() const;
	void Set(const Vec2&, const Vec2&);
	bool isAutoPlay() const;
	Direction nowDirection() const;
>>>>>>> develop
};