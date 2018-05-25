#pragma once
//______________________________ //
//|ポーズタスク                 |//
//|履歴：2018/05/23     劉韋君　|//
//|____________________________ |//
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
	int selectPos = 0;

public:
	Pause();
	virtual ~Pause();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();
	//☆☆☆☆//
	void Pause_draw();
	void PauseUpDate();
	enum Select {
		ToTitle, Stage, Ruselt,
	};
	Select select;
	bool PauseFlg;

	typedef std::shared_ptr<Pause> SP;
	static SP Create(bool = true);
};