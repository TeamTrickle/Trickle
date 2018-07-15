#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "VolumeControl/volumeControl.h"

class StageSelect : public TaskObject
{
	//アニメーション用class
	class Animation
	{
		Easing easing_x;
		Easing easing_y;
		Vec2 StartPos;
		Vec2 EndPos;
	public:
		Vec2 Move();
		Vec2 Move(const float time);
		Vec2 Move(const Easing::Name = Easing::Name::Linear, const Easing::Mode = Easing::Mode::InOut, const float = 10.f);
		Animation();
		void Set(Vec2&, Vec2&);
		bool isPlay() const;
	};

	//入り口の右側左側を判定させる用
	enum Direction
	{
		LEFT,
		RIGTH,
	};

	Animation camera_anim;

	Texture Testdoor;		//ドアの画像
	Texture Wall;           //壁の画像
	Texture LadderTex;

	//サウンドのファイル名格納
	std::string soundname;     
	std::string decisionsoundname;      //決定音

	std::vector<std::pair<Direction, float>> Entrance;	//扉に対しての向きとその座標
	//各処理管理
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
	//各処理関数
	void From1();
	void From2();
	void From3();
	void From4();

	unsigned __int64 timeCnt;
	int nowPos;
	unsigned __int8 doorNumber;			//設置するドアの枚数
	void ModeCheck();
	bool CheckTime(int);
	void GateClose();
	Easing camera_x;
	Easing camera_y;

	bool canVolControl;

public:
	StageSelect();
	virtual ~StageSelect();
	bool Initialize();
	void UpDate() override;
	void PauseUpDate() override;
	void Render2D() override;
	bool Finalize();

	enum State
	{
		Tutorial1,
		Tutorial2,
		Tutorial3,
		Stage1,
		Stage2,
		Stage3,
		ToTitle,
	};
	State state;
	Sound* sound;
	Sound decisionsound;
	VolumeControl volControl;

	typedef std::shared_ptr<StageSelect> SP;
	static SP Create(bool = true);
};