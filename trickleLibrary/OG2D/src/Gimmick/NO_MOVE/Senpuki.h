//|動くギミック  扇風機        |//
//|履歴：2018/03/29 横尾       |//
//|履歴：2018/03/30 横尾　     |//
//|履歴：2018/03/31 横尾       |//
//|履歴：2018/04/01 横尾       |//
//|履歴: 2018/04/02 横尾       |//
//|履歴: 2018/04/03 横尾       |//
//|履歴：2018/04/06 横尾       |//
//|履歴：2018/04/07 横尾       |//
//|履歴：2018/05/03 横尾       |//
//|____________________________|//

#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Switch.h"
#include "VolumeControl\volumeControl.h"

class Switch;

class Fan : public GameObject, public TaskObject {
public:
	enum Dir {
		LEFT,
		RIGHT,
	};
	void SetWindRange(Vec2&);
	//サウンド周りの情報
	bool startflag;
	Sound sound;
	VolumeControl volControl;

	typedef std::shared_ptr<Fan> SP;
	//座標、風の範囲(マス数)、向き、スイッチがオフ(初期状態)で稼働しているならtrue
	static Fan::SP Create(Vec2 pos, float r, Fan::Dir d, /*std::shared_ptr<Switch>& swich,*/ bool active, bool flag = true);

	void changeActive();				//自身の稼働状態を反転させる
	~Fan();

private:
	Fan();
	bool Initialize(Vec2 pos, float r, Dir d, /*std::shared_ptr<Switch>& swich,*/ bool active);
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理
	void SendWind();		//風で水蒸気を動かす

	//std::shared_ptr<Switch> swich_;		//オンオフに対応するスイッチ
	bool active_;						//自分が稼働しているならtrue(注：スイッチのboolと同じではない)

	Dir dir;		//向き
	Texture image;
	const Box2D Src = { 0,0,768 / 3,256 };
	float range;
	float movePos;
	int strength;
	std::string soundname;      //サウンドのファイル名格納
	std::string taskName;		//検索用

	struct Animetion
	{
		int animetionframe;
		int speed;
		void AnimetionMove(bool flag);				//アニメーションフレームを動かす
		void AnimetionReset();						//アニメーションの数値をリセットする
		void AnimetionSrc(Box2D& src, bool flag);	//アニメーションフレームを描画に影響させる
	};
	Animetion animetion;
	GameObject WindHitBase;

};




//class Fan : public GameObject, public TaskObject
//{
//	//-------------------------------------------
//	//各自で制作するときに使用するものはここに記述する
//	//-------------------------------------------
//public:
//
//	enum Dir
//	{
//		LEFT,
//		RIGHT,
//	};
//	void SetWindRange(Vec2&);
//	//サウンド周りの情報
//	bool startflag;
//	Sound sound;
//private:
//	//------------------
//	//固定化されている処理
//	//------------------
//	void SetSwitchTarget(std::shared_ptr<Switch>&);
//	void SetFanTarget(std::shared_ptr<Fan>&);
//	void SetFlag();
//	void Motion();
//	void DataInput();
//public:
//	std::shared_ptr<Switch> target;
//	std::shared_ptr<Fan> fantarget;
//	std::string taskName;
//	bool switchflag;
//	bool fanflag;
//	typedef std::shared_ptr<Fan> SP;
//	//常時動く扇風機の生成
//	static Fan::SP Create(Vec2 pos, float r, Fan::Dir d, bool = true);
//	//スイッチありの扇風機の生成
//	static Fan::SP Create(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Switch>& target, bool = true);
//	///例　A 動く B 動かない のようなフラグの入れ替えによってギミックを稼働させる場合
//	static Fan::SP Create(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Fan>& target, bool = true);
//	///例　A 動く B 動かない のようなフラグの入れ替えによってギミックを稼働させる場合(スイッチあり)
//	static Fan::SP Create(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Fan>& fanTarget, std::shared_ptr<Switch>& switchTarget, bool = true);
//	//-------------
//	//変更しないこと
//	//-------------
//	Fan();
//	virtual ~Fan();
//	//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
//
//	//扇風機を生成する場合・・・
//
//	//Vec2 pos = 座標　float r = 扇風機の風を送る範囲　Dir d = 扇風機の向き
//	//SP　Fan　= this 稼働しない ターゲットスイッチ  稼働中　になります
//	//SP  Switch = スイッチのフラグによって稼働しているかしていないかが決まります
//
//	//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
//
//
//	bool Initialize(Vec2 pos, float r, Dir d);
//	bool Initialize(Vec2 pos, float r, Dir d, std::shared_ptr<Fan> target);
//	bool Initialize(Vec2 pos, float r, Dir d, std::shared_ptr<Switch>&target);
//	bool Initialize(Vec2 pos, float r, Dir d, std::shared_ptr<Fan> fantarget, std::shared_ptr<Switch>&switchtarget);
//	void UpDate();			//更新処理
//	void Render2D();		//描画処理
//	bool Finalize();		//解放処理
//
//	bool GetSwitchFlag();
//private:
//	Dir dir;
//	Texture image;
//	const Box2D Src = { 0,0,768 / 3,256 };
//	float range;
//	float movePos;
//	int strength;
//	std::string soundname;      //サウンドのファイル名格納
//	struct Animetion
//	{
//		int animetionframe;
//		int speed;
//		void AnimetionMove(bool flag);				//アニメーションフレームを動かす
//		void AnimetionReset();						//アニメーションの数値をリセットする
//		void AnimetionSrc(Box2D& src, bool flag);	//アニメーションフレームを描画に影響させる
//	};
//	Animetion animetion;
//	GameObject WindHitBase;
//};
//
