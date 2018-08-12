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
		from8,
		from9,
		End,
	};
	Texture texCursor;

	Texture texEffect;
	Texture effect03;

	Texture GierLogo;
	Texture flowerLogo;

	Texture texLogo;

	Texture forTransform;
	//テスト追加
	Texture monitorTex;
	Texture fontTex;
	

	std::string soundname;
	std::string soundcursorname;
	std::string sounddecisionname;
	std::string soundflowername;

	//選択肢の文字の場所について
	Vec2 startPos;
	Vec2 closePos;
	Box2D textPos[2];
	Box2D cursorPos[3];

	//テスト追加
	Vec2 creditpos;      //クレジットに文字の位置
	Vec2 dataDeletepos;  //データを消す文字の位置
	Vec2 startsize;
	Vec2 closesize;
	Vec2 creditsize;
	Vec2 dataDeletesize;
	Vec2 yespos;         //データを消すときの選択肢の位置
	Vec2 nopos;
	float monitorSpos;    //モニターの左端の位置
	float monitorEpos;    //モニターの右端の位置

	enum nowmove
	{
		in,
		out,
		non
	};
	nowmove start;
	nowmove close;
	nowmove credit;
	nowmove dataDelete;

	enum Del
	{
		yes,
		no,
		yet
	};

	Del del;
	bool yesnoMode;

	Box2D intextsrc;
	Box2D outtextsrc;


	Texture waterTex;

	Animation cameraPos;
	Animation cameraSize;

	CameraManager cm;
	GameObject Logo;

	Mode mode;
	Mode preMode;

	Time demoTimer;
	const float DEMO_LIMIT = 10.f;
	float trans_a = 0.f;

	void ModeCheck();

	int nextTaskCheck;

	float tex_a;
	float cursor_a;
	__int8 cursorNum;      //0=start,1=credit,2=delete,3=exit,

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

	//テスト追加
	bool PressB();          //Bキーを押していたらtrueを返す
	bool pressB;
	Vec2 TextMoveout(Vec2 pos);        //選択肢の文字の移動について
	Vec2 TextMovein(Vec2 pos,Vec2 size,Vec2 outsize,float maxsize);
	Vec2 TextSizeout(Vec2 pos, Vec2 size, float maxsize);
	Vec2 TextSizein(Vec2 pos,Vec2 size,float maxsize);
	bool nowmoveL;
	bool nowmoveR;
	float startmax;
	float closemax;
	float creditmax;
	float datadeletemax;

	void CursorMove();
	void SetPauseEveryChild(const bool&);

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
