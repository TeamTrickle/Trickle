#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Chara : public GameObject, public TaskObject
{
	enum Direction						//向きを管理
	{
		LEFT,
		RIGHT,
	};
	Texture Image;
	Vec2 move;
	const float MOVE_SPEED;								//移動スピード
	const float JUMP_POWER;								//ジャンプパワー
	const float MAX_FALL;								//落下最大速度
	const float GRAVITY;		//重力加速度
	const float FIN_SPEED;								//摩擦
	Direction direction;										//向きを格納する変数
	std::string taskName;										//名
	int AnimCnt;
	bool isAuto;
	bool isCollision;
	int MoveCnt;
	__int8 isCollisionNow;
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
};