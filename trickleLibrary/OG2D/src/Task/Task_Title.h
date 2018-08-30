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
		from10,
		from11,
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
	//表示するサイズ格納
	Vec2 startsize;      
	Vec2 closesize;
	Vec2 creditsize;
	Vec2 dataDeletesize;
	//データを消すときの選択肢の位置
	Vec2 yespos;         
	Vec2 nopos;
	float monitorSpos;    //モニターの左端の位置
	float monitorEpos;    //モニターの右端の位置
	enum nowmove          //モニター内の文字の動き
	{
		in,       //入ってくる
		out,      //出ていく
		non       //待機中
	};
	nowmove start;
	nowmove close;
	nowmove credit;
	nowmove dataDelete;

	enum Del             //データを消すか消さないかの最終確認用
	{
		yes,
		no,
	};
	Del del;

	Box2D intextsrc;      //モニターに入ってくるときのsrcの挙動
	Box2D outtextsrc;     //モニターから出ていくときのsrcの挙動


	Texture waterTex;

	Animation cameraPos;
	Animation cameraSize;

	CameraManager cm;
	GameObject Logo;

	Mode mode;
	Mode preMode;

	Time demoTimer;
	int curPlayVideo = 0;
	const static std::string DEMO_VIDEOS[];
	const float DEMO_LIMIT = 10.f;
	float trans_a = 0.f;

	void ModeCheck();

	int nextTaskCheck;

	float tex_a;
	float cursor_a;
	__int8 cursorNum;      //0=start,1=credit,2=delete,3=exit,
	float press_a;
	float press_delta_a;

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
	//選択肢の文字の移動について
	Vec2 TextMoveout(Vec2 pos);        
	Vec2 TextMovein(Vec2 pos,Vec2 size,Vec2 outsize,float maxsize);
	Vec2 TextSizeout(Vec2 pos, Vec2 size, float maxsize);
	Vec2 TextSizein(Vec2 pos,Vec2 size,float maxsize);

	bool nowmoveL;        //現在左に動いているか
	bool nowmoveR;        //現在右に動いているか
	//文字の最大横サイズ格納
	float startmax;
	float closemax;
	float creditmax;
	float datadeletemax;

	void CursorMove();      //使わなくなって削除予定

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
