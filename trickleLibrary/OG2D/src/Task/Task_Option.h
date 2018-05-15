#pragma once

//______________________________//
//|オプションタスク             |//
//|履歴   :2018/04/17薄井恭香   |//
//|                             |//
//|_____________________________|//
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Map\Map.h"
#include "OGSystem\Audio\Sound.h"

class Option : public TaskObject
{
	Texture texBack;   	std::string soundName;         //サウンドのファイル名
            //仮の背景画像のファイル名
	Texture texBar;               //仮のボリューム表示画像
	Texture texGear;               //仮のボリューム表示画像
public:
	Option();
	virtual ~Option();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();

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
	typedef std::shared_ptr<Option> SP;
	static SP Create(bool = true);
};