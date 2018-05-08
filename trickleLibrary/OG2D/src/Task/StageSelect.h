#pragma once
#include "Win\WinMain.h"
#include "OGSystem\OGsystem.h"

class StageSelect
{
	Texture texBack;
	Texture texCursor;
	Texture texTutorial;
	Texture texStage1;
	Texture texStage2;
	Texture texToTitle;

	Vec2 cursorPos;
	Vec2 tutorialPos;
	Vec2 stage1Pos;
	Vec2 stage2Pos;
	Vec2 toTitlePos;

public:
	void Initialize();
	TaskFlag UpDate();
	void Render();
	void Finalize();

	void CursorMove();

	enum State
	{
		Tutorial,
		Stage1,
		Stage2,
		ToTitle,
	};
	State state;

};