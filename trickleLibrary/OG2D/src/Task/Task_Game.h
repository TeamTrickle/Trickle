#pragma once
//______________________________//
//|タスクサンプル               |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//
#include "Win\WinMain.h"
#include "CollisionManager\CollisionManager.h"
#include "OGSystem\OGsystem.h"
#include "Player\Player.h"
#include "Back\Back.h"
#include "Map\Map.h"
#include "Water\water.h"
#include "Bucket\bucket.h"
#include "Goal\Goal.h"
#include "Block\block.h"
#include "Gimmick\NO_MOVE\Kanetuki.h"
#include "Gimmick\NO_MOVE\Seihyouki.h"
#include "Gimmick\NO_MOVE\Senpuki.h"
#include "Gimmick\NO_MOVE\Switch.h"


class Game
{
public:
	void Initialize();
	TaskFlag Update();
	void Render2D();
	void Finalize();
	//☆☆☆☆//
	//追加変数//
	//☆☆☆☆//
	Player player;
	//std::vector<Bucket*> bucket;
	Block block;
	Bucket bucket;
	Back back;
	Map map;
	std::vector<Water*> water;
	CollisionManager cm;
	int timecnt;
	Goal goal;

	//ジャスティン風
	/*Senpuki senpuki;
	Seihyouki seihyouki;
	Kanetuki kanetuki;
	Switch switch_;*/

	//横田さん風
	Switch swich[2];
	Fan fan[2];

};