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
	Texture totitleTex;		//タイトルに戻る看板

	//サウンドのファイル名格納
	std::string soundname;     
	std::string decisionsoundname;      //決定音

	std::vector<std::pair<Direction, float>> Entrance;	//扉に対しての向きとその座標
	//各処理管理
	enum Mode
	{
		Non,
		createTask,
		objectMoveTask,
		waitTask,
		afterMoveTask,
		End,
	};
	Mode mode;
	Mode preMode;
	//各処理関数
	void CreateTask();
	void ObjectMoveTask();
	void WaitTask();
	void AfterMoveTask();

	unsigned __int64 timeCnt;
	int nowPos;
	unsigned __int8 doorNumber;			//設置するドアの枚数
	bool isPause;
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