#pragma once
//______________________________//
//|プレイヤ                    |//
//|履歴：2018/03/23横田	       |//
//|履歴：2018/03/26劉韋君　    |//
//|履歴：2018/03/29劉韋君　    |//
//|履歴：2018/03/30木務　    |//
//|____________________________|//
#include "CollisionManager\CollisionManager.h"
#include "Bucket\bucket.h"
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Gimmick\NO_MOVE\Switch.h"
#include "Block\block.h"

class Player :public Object 
{
	struct Move {
		Vec2 est;
		float angle;
	};
	enum Direction
	{
		LEFT,
		RIGHT,
	};
	const std::array<std::string, 3> WALKABLE_CHIPS{
		"Floor",
		"Soil",
		"Net"
	};
	enum State
	{
		NORMAL,		//通常
		LADDER,		//はしご中
		BUCKET,		//バケツ所持
		ANIMATION,	//アニメーション中
	};
	enum Motion
	{
		Normal,		//通常
		Jump,		//ジャンプ
		Ladder,		//はしご
		Fall,		//落下
	};
	class Animation
	{
	public:
		Vec2 animationVec;
		Vec2 startVec;
		Vec2 endVec;
	public:
		void SetAnimaVec(Vec2 start_, Vec2 end_);
		void Initialize();
		Vec2 Move();
		bool isMove();
	};
private:
	const std::string fileName = "player.png";
	const float MOVE_SPEED = 5.f;								//移動スピード
	const float JUMP_POWER = -20.f;								//ジャンプパワー
	const float MAX_FALL = 10.f;
	const float GRAVITY = (9.8f / 60.f / 60.f * 32) * 5;								//重力加速度
	const float FIN_SPEED = 0.5f;								//摩擦
	bool CheckJump;												//ジャンプ判定
	bool CheckGravity;											//重力加速度判定
	int moveCnt;
	Texture playerimg;
	Move move;
	Vec2 est;													//移動量
	Direction direction;										//向きを格納する変数
	Motion motion;
	State state;
	std::vector<Object*> objects;
	std::vector<Bucket*> buckets;
	std::vector<Block*> blocks;
	Bucket* haveBucket;
	Animation animation;
	int inv;
private:
	bool HeadCheck();
	bool FootCheck();
	bool HeadCheck(std::string objname_, int n = 0);
	bool FootCheck(std::string objname_, int n = 0);
	void MoveCheck(Vec2 est);
	void MoveCheck(Vec2 est, std::string objname_);
	void Friction();
	bool BucketHit();
	void BucketMove();
	bool BlockHit();
	void DebugFootCheck();
	void DebugHeadCheck();
	bool ObjectHit(std::string objname_);
public:
	Player();
	~Player();
	void Initialize();
	void Update();
	void Render();
	void Finalize();
	void AddObject(Object* obj_);
	void DeleteObject(Object* obj_);
	void AllDelete();
	void AddBucket(Bucket* bucket);
	bool DeleteBucket(Bucket* bucket);
	void AddBlock(Block* block);
	bool DeleteBlock(Block* block);
	Vec2 GetEst() const;
	bool InputLeft() {
		return gameEngine->in.on(Input::CL);
	}
	bool InputRight() {
		return gameEngine->in.on(Input::CR);
	}
	bool InputDown() {
		return gameEngine->in.on(Input::CD);
	}
	bool InputUp() {
		return gameEngine->in.on(Input::CU);
	}
};