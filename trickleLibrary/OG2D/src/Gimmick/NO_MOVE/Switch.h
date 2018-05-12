//______________________________//
//|動くギミック  スイッチ      |//
//|履歴：2018/03/29 横尾	   |//
//|履歴：2018/03/31 横尾　     |//
//|履歴：2018/04/01 横尾       |//
//|履歴: 2018/04/02 横尾       |//
//|履歴: 2018/04/03 横尾       |//
//|履歴：2018/04/07 横尾       |//
//|____________________________|//
#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"



class Switch : public GameObject, public TaskObject
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
public:
	
	bool isON();
	void ON_OFF();
	//void SetTarget(GameObject* t);
private:
	Texture image;
	std::string path;
	bool is_on;
	//------------------
	//固定化されている処理
	//------------------
public:
	std::string taskName;
	virtual ~Switch();
	typedef std::shared_ptr<Switch> SP;
	static Switch::SP Create(Vec2& pos,bool = true);
	Switch();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize(Vec2& pos);	//初期化処理
	void UpDate();				//更新処理
	void Render2D();			//描画処理
	bool Finalize();			//解放処理
};