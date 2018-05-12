#pragma once

#include "OGSystem\OGsystem.h"

class StageSelect : public TaskObject
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
	StageSelect();
	virtual ~StageSelect();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();

	void CursorMove();

	enum State
	{
		Tutorial,
		Stage1,
		Stage2,
		ToTitle,
	};
	State state;
	typedef std::shared_ptr<StageSelect> SP;
	static SP Create(bool = true);
};