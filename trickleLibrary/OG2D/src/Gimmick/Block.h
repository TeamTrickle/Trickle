#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Win\WinMain.h"

//ボックス本体のクラス--------------------------------------------------------------------------------
class GimmickB :public Object
{
public:
	Texture BlockImg;
	std::string fileName = "Collision.png";
	Box2D HitR;
	Box2D HitL;
	bool hitRight;     //右側当たり判定用
	bool hitLeft;      //左側当たり判定用
	bool hitbottom;    //地面当たり判定用
	float speed;       //押したときの移動速度

	//bool MapHit(Box2D map, Box2D block);

	void Initialize();
	TaskFlag UpDate();
	void Render();
	void Finalize();
};


