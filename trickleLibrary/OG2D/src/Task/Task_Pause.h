#pragma once
//______________________________//
//|ポーズタスク                 |//
//|履歴：2018/05/23     劉韋君　|//
//|____________________________ |//
#include "OGSystem\OGsystem.h"
#include "Map\Map.h"

class Pause :public TaskObject
{
	//画像変数
	Texture texCursor;
	Texture texRestart;
	Texture texReturn;
	Texture texStageSelect;
	Texture texTransparentBack;
	//位置変数
	Vec2 RestartPos;
	Vec2 ReturnPos;
	Vec2 stageselectPos;
	Vec2 cursorPos;
	Vec2 transparentbackPos;

	int selectPos = 0;

	unsigned int gearAng;

	//サウンドのファイル名格納
	std::string cursorsoundname;
	std::string dicisionsoundname;

public:
	Pause();
	virtual ~Pause();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();
	//メソッド
	void Pause_draw();
	void PauseUpDate();
	bool imageFlag;
	//選択肢の状態フラグ
	enum Select {
		Restart, Stage, Return,
	};
	Select select;

	//カメラ移動
	bool Pause::InputLeft() {
		return OGge->in->key.on(In::A) || OGge->in->on(In::RL);
	}
	bool Pause::InputRight() {
		return OGge->in->key.on(In::D) || OGge->in->on(In::RR);
	}
	bool Pause::InputDown() {
		return OGge->in->key.on(In::S) || OGge->in->on(In::RD);
	}
	bool Pause::InputUp() {
		return OGge->in->key.on(In::W) || OGge->in->on(In::RU);
	}

	typedef std::shared_ptr<Pause> SP;
	static SP Create(bool = true);

	//サウンド生成
	Sound cursorsound;
	Sound decisionsound;
};