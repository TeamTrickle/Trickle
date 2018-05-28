#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class StageSelect : public TaskObject
{
	class Animation
	{
		Easing easing_x;
		Easing easing_y;
		Vec2 StartPos;
		Vec2 EndPos;
	public:
		Vec2 Move();
		Animation();
		void Set(Vec2&, Vec2&);
		bool isPlay() const;
	};

	//ì¸ÇËå˚ÇÃâEë§ç∂ë§ÇîªíËÇ≥ÇπÇÈóp
	enum Direction
	{
		LEFT,
		RIGTH,
	};

	Animation camera_anim;

	Texture texBack;
	Texture texCursor;
	Texture texTutorial;
	Texture texStage1;
	Texture texStage2;
	Texture texToTitle;

	Texture Testdoor;

	GameObject* gate[3];

	Vec2 cursorPos;
	Vec2 tutorialPos;
	Vec2 stage1Pos;
	Vec2 stage2Pos;
	Vec2 toTitlePos;

	std::vector<std::pair<Direction, float>> Entrance;

	enum Mode
	{
		Non,
		from1,
		from2,
		from3,
		from4,
		End,
	};
	Mode mode;
	Mode preMode;
	void From1();
	void From2();
	void From3();
	void From4();
	int timeCnt;
	int nowPos;
	void ModeCheck();
	Easing camera_x;
	Easing camera_y;

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