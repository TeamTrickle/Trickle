#pragma once
//______________________________//
//|プレイヤ                     |//
//|履歴：2018/03/23横田	       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Player :public Object
{
public:
	Texture playerimg;
	std::string fileName = "player.png";
	bool hitcheck;

	void Initialize();
	void UpDate();
	void Render();
	void Finalize();
	//☆☆☆☆//-----------------------------------------------------------------------------
	//追加変数//-----------------------------------------------------------------------------
	//☆☆☆☆//-----------------------------------------------------------------------------

	//X方向の移動スピード
	float speed;

	bool jumpFlag = false;
	Vec2 est;
	const float JUMP_POWER = -30.f;
	const float GRAVITY = 9.8f;

	//☆☆☆☆//-----------------------------------------------------------------------------
	//クラスのメンバ関数
	//☆☆☆☆//-----------------------------------------------------------------------------
	//ジャンプのプロトタイプ宣言
	void JumpMove();
};


