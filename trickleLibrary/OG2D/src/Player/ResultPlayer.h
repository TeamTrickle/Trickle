#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
class ResultPlayer : public GameObject , public TaskObject 
{
public:
	enum State
	{
		Normal,	//何もしない
		Walk,	//歩くモーション
		Smail,	//喜ぶモーション
		Stop,	//ストップ中
	};
private:
	struct Animetion
	{
		int animetionCnt;				//アニメーションカウンタ

		Box2D ReturnSrc(Box2D, State);	//アニメーションのSrcを返す
		void Reset();					//アニメーションのリセット
		void ResetAnimetionCnt();		//アニメーションカウントをリセット
		void MotionChenge(State);		//アニメーションを変更する
		State motion;					//モーション

		//モーションに関する変数
		int toSmailCnt = 0;				//喜ぶモーションにするまでの時間を格納する
		bool SmailChangeCheck();		//喜ぶモーションに切り替えて良いかを返す
		bool smailflag;					//喜ぶフラグ
		void SmailMotion();				//喜びモーションを入れる
	};

	Texture image;
	std::string filePath;
	Vec2 moveVec;
	Animetion animetion;
	void Move();
	void Think();
	void Motion();
	const Box2D Src = { Vec2(0, 575), Vec2(586, 575) };

	//リザルト画面へのフラグ関数
	bool walkstop;
	void ResetWalkStop();
	

public:
	typedef std::shared_ptr<ResultPlayer> SP;
	ResultPlayer();
	virtual ~ResultPlayer();
	std::string taskName;

	bool Initialize(Vec2& pos,Vec2& speed);
	void UpDate();
	void Render2D();
	bool Finalize();
	static ResultPlayer::SP Create(Vec2 pos,Vec2 speed = Vec2(1,0) ,bool = true);

	//リザルト画面に関連するフラグ関数
	bool GetResetWalkStop();
};