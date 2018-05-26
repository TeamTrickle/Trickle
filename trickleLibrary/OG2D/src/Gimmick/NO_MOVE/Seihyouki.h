#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Switch.h"
class Seihyouki : public GameObject, public TaskObject
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
private:
	void toIce();							//氷にする
	void SetSwitchFlag(std::shared_ptr<Switch>&);
	void GetFlag();
	bool GetSwitchFlag();
private:
	GameObject hitBace;
	bool switchflag;
	//------------------
	//固定化されている処理
	//------------------
public:
	std::string taskName;
	std::shared_ptr<Switch> target;
	virtual ~Seihyouki();
	typedef std::shared_ptr<Seihyouki> SP;
	static Seihyouki::SP Create(Vec2& pos, bool = true);
	static Seihyouki::SP Create(Vec2& pos,std::shared_ptr<Switch>& target,bool = true);
	Seihyouki();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize(Vec2&);		//初期化処理
	bool Initialize(Vec2&,std::shared_ptr<Switch>& target);		//初期化処理
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理

private:
	int movetime;					//氷にするまでの格納するフレーム数
	const int movetime_ice = 20;	//氷にするまで・・・
};