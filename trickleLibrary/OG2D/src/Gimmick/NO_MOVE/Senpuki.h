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

#include "Gimmick\NO_MOVE\Switch.h"
#include "Water\water.h"

class Switch;

class Fan : public GameObject, public TaskObject
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
public:
	std::vector<Switch*> switches;		//自身の稼働にかかわっているスイッチ一覧

	enum Dir
	{
		LEFT,
		RIGHT,
	};
	Fan(Vec2);
	bool Initialize(Vec2 pos, float r, Dir d, bool activ);
	void AddSwitch(Switch* swit);
	void ChangeState();
	void SetTexture(Texture*);
	void SetWindRange(Vec2&);

	//WaterのVector情報のアドレス値を受け取る
	void SetWaterPool(Water*);
	bool DeleteWaterPool(Water*);
	void Motion(Water*);
private:
	//------------------
	//固定化されている処理
	//------------------
public:
	std::string taskName;
	virtual ~Fan();
	typedef std::shared_ptr<Fan> SP;
	static Fan::SP Create(bool, Vec2 pos, float r, Fan::Dir d, bool activ);
	Fan();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize();		//初期化処理
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理
private:
	Dir dir;
	Texture* image;
	float range;
	float movePos;
	bool active;
	int strength;
	std::vector<Water*>water;
	GameObject WindHitBase;
};

