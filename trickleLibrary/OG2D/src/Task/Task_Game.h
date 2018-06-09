#pragma once
//______________________________//
//|タスクサンプル               |//
//|履歴：2018/03/20金子翔       |//
//|履歴：2018/04/17劉韋君　    |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "UI\UI.h"

class UI;

class Game : public TaskObject
{
public:
	typedef std::shared_ptr<Game> SP;
	static SP Create(bool = true);
	Game();
	virtual ~Game();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();
	//☆☆☆☆//
	//追加変数//
	//☆☆☆☆//
	int timecnt;

	Sound sound;
private:
	//---------------------------------------------------------------------
	//メンバー関数
	//---------------------------------------------------------------------
	//カメラ処理
	void Camera_move();
	
	//ギミックの追加
	Vec2 _waterpos;

	Texture waterTex;
	Texture waterRed;
	Texture waterBlue;
	Texture waterPurple;
	Texture playerTex;
	Texture fanTex;
	Texture fireice;
	Texture PaintTex;
	Texture EffectTest;
	Texture Effectsond;
	std::string gamesoundname;
	std::string tutorialsoundname;

	//UI----------------------------------------
	std::shared_ptr<UImanager> UImng_;
};