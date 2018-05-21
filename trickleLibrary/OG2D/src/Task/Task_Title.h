#pragma once
//______________________________//
//|タイトルタスク               |//
//|履歴：2018/03/20金子翔       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "CameraManager\CameraManager.h"

class Title:public TaskObject
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
	Texture texStart;
	Texture texClose;
	Texture texPause;

	Texture texLogo;

	Vec2 startPos;
	Vec2 pausePos;
	Vec2 closePos;
	Vec2 cursorPos[3];

	//Texture back;
	Texture waterTex;

	Animation cameraPos;
	Animation cameraSize;

	GameObject testObj;
	//Texture test;
	CameraManager cm;
	GameObject Logo;

	Mode mode;
	Mode preMode;

	void ModeCheck();

	int nextTaskCheck;

	float tex_a;
	float cursor_a;
	__int8 cursorNum;

public:
	Title();
	virtual ~Title();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();

	int timeCnt;

	void CursorMove();
	//☆☆☆☆//
	//追加変数//
	//☆☆☆☆//
	Sound sound;

	enum State
	{
		Start,        //ゲームスタート
		Pause,         //設定
		Close        //ゲームを閉じる
	};
	State state;

	typedef std::shared_ptr<Title> SP;
	static SP Create(bool = true);
};

class Chara : public GameObject, public TaskObject
{
	enum Direction						//向きを管理
	{
		LEFT,
		RIGHT,
	};
	Texture Image;
	Vec2 move;
	const float MOVE_SPEED = 5.f;								//移動スピード
	const float JUMP_POWER = -13.f;								//ジャンプパワー
	const float MAX_FALL = 15.f;								//落下最大速度
	const float GRAVITY = (9.8f / 60.f / 60.f * 32) * 10;		//重力加速度
	const float FIN_SPEED = 0.5f;								//摩擦
	Direction direction;										//向きを格納する変数
	std::string taskName;										//名
	int AnimCnt;
	bool isAuto;
	bool isCollision;			
	int MoveCnt;
public:
	Chara(std::string&,Vec2&);
	virtual ~Chara();
	typedef std::shared_ptr<Chara> SP;
	static SP Create(std::string&, Vec2&, bool = true);
	void UpDate();
	void Render2D();
	void Friction();
	void MoveCheck(Vec2&);
	bool FootCheck();
	bool Jump();
	void AutoMove();
	void ManualMove(Vec2&);
};