#pragma once
//______________________________//
//|タイトルタスク               |//
//|履歴：2018/03/       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Map\Map.h"

class Pause :public TaskObject
{
	Texture texCursor;
	Texture texTitle;
	Texture texRuselt;
	Texture texStageSelect;
	Texture texTransparentBack;
	Vec2 titlePos;
	Vec2 ruseltPos;
	Vec2 stageselectPos;
	Vec2 cursorPos;
	Vec2 transparentbackPos;

	int nextTaskCheck;
	int sex = 0;

public:
	Pause();
	virtual ~Pause();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();

	//☆☆☆☆//
	//追加変数//
	//☆☆☆☆//
	Sound sound;

	//ポーズ処理
	void Pause_Initialize(/*Vec2& npt_*/);
	void Pause_move();
	void Pause_draw();
	//ポーズ
	enum Select
	{
		ToTitle,
		Stage,
		Ruselt,
	};
	Select select;
	bool PauseFlg;
	void PauseUpDate();

	typedef std::shared_ptr<Pause> SP;
	static SP Create(bool = true);
};
