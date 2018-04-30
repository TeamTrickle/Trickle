#pragma once

//______________________________//
//|オプションタスク             |//
//|履歴   :2018/04/17薄井恭香   |//
//|                             |//
//|_____________________________|//
#include "Win\WinMain.h"
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Map\Map.h"
#include "CollisionManager\CollisionManager.h"
#include "OGSystem\Audio\Sound.h"

class Option : public Sound
{
	Texture texBack;   	std::string soundName;         //サウンドのファイル名
            //仮の背景画像のファイル名
	Texture texBar;               //仮のボリューム表示画像
	Texture texGear;               //仮のボリューム表示画像
public:
	void Initialize();
	TaskFlag Update();
	void Render();
	void Finalize();

	//ボリュームの格納
	float vol;
	//描画用の変数
	float gearPos;
	float barwidth;
	float nowVol;

	//サウンドの生成
	Sound sound;
	//サウンドの初期設定
	void Set();
	//サウンドの音量調整
	void VolControl();
	//描画の移動
	void DrawVol();
};