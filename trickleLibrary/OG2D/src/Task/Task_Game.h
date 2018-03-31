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

#include "Object\Senpuki.h"
#include "Object\Switch.h"

class Game
{
public:
	void Initialize();
	TaskFlag UpDate();
	void Render2D();
	void Finalize();
	//☆☆☆☆//
	//追加変数//
	//☆☆☆☆//
	Player player;
	Senpuki senpuki;                             //_OTKでの処理エラーの場合、コンストラクタのミスが高いです
	Switch switch_;                              //クラスの変数宣言
	//std::vector<Bucket*> bucket;
	Bucket bucket;
	Back back;
	Map map;
	std::vector<Water*> water;
	CollisionManager cm;
	int timecnt;
	Goal goal;
};