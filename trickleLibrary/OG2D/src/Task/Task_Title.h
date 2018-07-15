#pragma once
//______________________________//
//|タイトルタスク               |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "CameraManager\CameraManager.h"
#include "VolumeControl/volumeControl.h"

class Title :public TaskObject
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



	enum Mode
	{
		Non,
		from1,
		from2,
		from3,
		from4,
		from5,
		from6,
		from7,
		End,
	};
	Texture texCursor;

	Texture texEffect;
	Texture effect03;

	Texture GierLogo;
	Texture flowerLogo;

	Texture texLogo;
	

	std::string soundname;
	std::string soundcursorname;
	std::string sounddecisionname;
	std::string soundflowername;

	Vec2 startPos;
	Vec2 closePos;
	Box2D textPos[2];
	Box2D cursorPos[3];

	Texture waterTex;

	Animation cameraPos;
	Animation cameraSize;

	CameraManager cm;
	GameObject Logo;

	Mode mode;
	Mode preMode;

	void ModeCheck();

	int nextTaskCheck;

	float tex_a;
	float cursor_a;
	__int8 cursorNum;

	int gierCnt;
	bool isGierAng;
	float flowerVolume;
	bool isSkip;

	void SkipMove();
	bool skipInoutFlag;

public:
	Title();
	virtual ~Title();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();
	void Skip();
	void BackTitleSkip();
	int timeCnt;

	void CursorMove();

	enum State
	{
		Start,        //ゲームスタート
		Pause,         //設定
		Close        //ゲームを閉じる
	};
	State state;
	Sound* sound;
	Sound cursorsound;
	Sound decisionsound;
	Sound flowersound;
	VolumeControl volControl;

	bool canVolControl;

	bool soundstart;

	typedef std::shared_ptr<Title> SP;
	static SP Create(bool = true);
};
