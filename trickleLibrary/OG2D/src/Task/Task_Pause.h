#pragma once

/*
* @file Task_Pause.h
* @brief ポーズタスククラス
* @author yokota_mariko
* @date 2018.9.9
*/

#include "OGSystem\OGsystem.h"
#include "Map\Map.h"

class Pause : public TaskObject
{
	//! 画像、あとでResoureManagerに登録する
	Texture texCursor;
	Texture* texChoices;
	Texture texTransparentBack;
	//! テクスチャのカラー
	Color texColor;
	//! 位置変数
	Vec2 RestartPos;
	Vec2 ReturnPos;
	Vec2 stageselectPos;
	Vec2 cursorPos;
	//! カーソル歯車アングル
	unsigned int gearAng;
	//! カメラが動いているか
	bool isCameraMoving;
	//! カーソル位置識別用
	int stateNum;
	//! サウンドのファイル名格納
	std::string cursorsoundname;
	std::string dicisionsoundname;
	//! マップタスク
	std::shared_ptr<Map> map;

	Pause();
	void ReleasePause();
	void MoveCamera();
	void CreateNextTask();
	void CreateLoad();
	bool checkCameraHitMap(Vec2 v);
	void setTexPos();
	void moveCursor();
public:
	//サウンド変数
	Sound cursorsound;
	Sound decisionsound;
	//! 選択肢の状態一覧
	enum State {
		Non,			//! 未定義
		BackToGame,		//! ゲームに戻る
		Restart,		//! リスタート
		StageSelect,	//! ステージセレクトに戻る
	};
	//! 選択肢の状態
	State state;

	virtual ~Pause();
	bool Initialize();
	void Render2D();
	bool Finalize();
	void PauseUpDate();
	bool imageFlag;
	//! スマートポインタの別名定義
	typedef std::shared_ptr<Pause> SP;
	//! タスク生成メソッド
	static SP Create(bool flag = true);
};