<<<<<<< HEAD
//#pragma once
//#include "OGSystem\OGsystem.h"
//#include "Object\Object.h"
//class ResultPlayer : public GameObject , public TaskObject 
//{
//public:
//	enum State
//	{
//		Normal,	//何もしない
//		Walk,	//歩くモーション
//		Smail,	//喜ぶモーション
//		Stop,	//ストップ中
//	};
//private:
//
//	//アニメーション関連
//	struct Animetion
//	{
//		int animetionCnt;				//アニメーションカウンタ
//
//		Box2D ReturnSrc(Box2D, State);	//アニメーションのSrcを返す
//		void Reset();					//アニメーションのリセット
//		void ResetAnimetionCnt();		//アニメーションカウントをリセット
//		void MotionChenge(State);		//アニメーションを変更する
//		void AnimetionMove();			//アニメーションカウントをカウントします
//		State motion;					//モーション
//
//		//モーションに関する変数
//		const int toSmailCnt = 200;				//喜ぶモーションにするまでの時間を格納する
//
//		//喜ぶモーションが終了したか返す
//		bool  SmailMotionIsPlay();
//
//		//Srcの喜びモーションをリセット
//		void  ResetSrc(Box2D&);
//	};
//	Animetion animetion;
//	
//	//移動関連
//	Vec2 moveVec;
//	void Move();
//	
//	//Playerの状態関連
//	void Think();
//	void Motion();
//	
//
//	//画像関連
//	Texture image;
//	std::string filePath;
//	const Box2D Src = { Vec2(0, 575), Vec2(586, 575) };
//
//	//リザルト画面へのフラグ関数
//	bool walkstop;
//	bool keyflag;
//	void ResetWalkStop();
//	
//	//タスク関連
//	std::string taskName;
//	void UpDate();
//	void Render2D();
//	bool Finalize();
//
//public:
//	typedef std::shared_ptr<ResultPlayer> SP;
//	ResultPlayer();
//	virtual ~ResultPlayer();
//
//	bool Initialize(Vec2& pos,Vec2& speed);
//	static ResultPlayer::SP Create(Vec2 pos,Vec2 speed = Vec2(1,0) ,bool = true);
//
//	//リザルト画面に関連するフラグ関数
//	bool GetResetWalkStop();
//};
=======
#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Player.h"
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

	//アニメーション関連
	struct Animetion
	{
		int animetionCnt;				//アニメーションカウンタ

		Box2D ReturnSrc(Box2D, State);	//アニメーションのSrcを返す
		void Reset();					//アニメーションのリセット
		void ResetAnimetionCnt();		//アニメーションカウントをリセット
		void MotionChenge(State);		//アニメーションを変更する
		void AnimetionMove();			//アニメーションカウントをカウントします
		State motion;					//モーション

		//モーションに関する変数
		const int toSmailCnt = 200;				//喜ぶモーションにするまでの時間を格納する

		//喜ぶモーションが終了したか返す
		bool  SmailMotionIsPlay();

		//Srcの喜びモーションをリセット
		void  ResetSrc(Box2D&);
	};
	Animetion animetion;
	
	//移動関連
	Vec2 moveVec;
	void Move();
	void Jump();
	
	//Playerの状態関連
	void Think();
	void Motion();
	

	//画像関連
	Texture image;
	Texture smail;
	std::string filePath;
	const Box2D Src[2] =
	{
		Box2D(Vec2(0, 575), Vec2(586, 575)),
		Box2D(Vec2(0,0),Vec2(1923 / 3 , 1068 / 2))
	};

	//リザルト画面へのフラグ関数
	bool walkstop;
	bool keyflag;
	void ResetWalkStop();
	
	//タスク関連
	std::string taskName;
	void UpDate();
	void Render2D();
	bool Finalize();

public:
	typedef std::shared_ptr<ResultPlayer> SP;
	ResultPlayer();
	virtual ~ResultPlayer();

	bool Initialize(Vec2& pos,Vec2& speed);
	static ResultPlayer::SP Create(Vec2 pos,Vec2 speed = Vec2(1,0) ,bool = true);

	//リザルト画面に関連するフラグ関数
	bool GetResetWalkStop();
};
>>>>>>> develop
