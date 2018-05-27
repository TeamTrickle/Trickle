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

class Switch;

class Fan : public GameObject, public TaskObject
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
public:

	enum Dir
	{
		LEFT,
		RIGHT,
	};
	void SetWindRange(Vec2&);
private:
	//------------------
	//固定化されている処理
	//------------------
	void SetSwitchFlag(std::shared_ptr<Switch>&);
	bool GetSwitchFlag();
	void GetFlag();
	void Motion();
public:
	std::shared_ptr<Switch> target;
	std::string taskName;
	bool switchflag;
	virtual ~Fan();
	typedef std::shared_ptr<Fan> SP;
	static Fan::SP Create(Vec2 pos, float r, Fan::Dir d, bool = true);
	static Fan::SP Create( Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Switch>& target,bool = true);
	//-------------
	//変更しないこと
	//-------------
	Fan();
	bool Initialize(Vec2 pos, float r, Dir d);
	bool Initialize(Vec2 pos, float r, Dir d,std::shared_ptr<Switch>&target);
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理
private:
	Dir dir;
	Texture image;
	const Box2D Src = { 0,0,768 / 3,256 };
	float range;
	float movePos;
	int strength;
	struct Animetion
	{
		int animetionframe;
		int speed;
		void AnimetionMove(bool flag);				//アニメーションフレームを動かす
		void AnimetionReset();						//アニメーションの数値をリセットする
		void AnimetionSrc(Box2D& src,bool flag);	//アニメーションフレームを描画に影響させる
	};
	Animetion animetion;
	GameObject WindHitBase;
};

