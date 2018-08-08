#pragma once
//______________________________//
//|タスクサンプル               |//
//|履歴：2018/03/20金子翔       |//
//|履歴：2018/04/17劉韋君　    |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "UI\UI.h"
#include "VolumeControl/volumeControl.h"
#include "CameraManager\CameraManager.h"
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

	//サウンド関連
	Sound sound;
	VolumeControl volControl;
	bool canvolControl;

	CameraEasing ce;
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
	Texture texSteam;
	Texture goalTex;
	Texture goalDirectionTex;
	Texture arrowflower;
	Texture doorTex;
	Texture WswitchTex;
	Texture pipeTex;
	std::string gamesoundname;
	std::string tutorialsoundname;

	//UI----------------------------------------
	std::shared_ptr<UImanager> UImng_;
	//カメラの即移動防止のための拡張機能
	void CameraSetPos(const Vec2&);
};