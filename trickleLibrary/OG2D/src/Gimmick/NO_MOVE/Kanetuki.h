#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Gimmick\NO_MOVE\Switch.h"

class Kanetuki : public GameObject, public TaskObject
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
public:
	std::shared_ptr<Switch> target;
private:
	bool switchflag;
	//------------------
	//固定化されている処理
	//-----------------
	std::string taskName;
	typedef std::shared_ptr<Kanetuki> SP;
	Kanetuki();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize(Vec2&);
	bool Initialize(Vec2&,std::shared_ptr<Switch>&);
	//初期化処理
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理
	void GetFlag();
private:
	const int Fire_time_LIQUID = 30;	//加熱する時間 液体
	const int Fire_time_SOLID = 20;	    //加熱する時間 個体
	int Fire_movetime;					//燃やす時間を格納する

	//状態遷移
	void toSteam();						//水から水蒸気にする
	//指定スイッチのフラグを代入する
	void SetSwitchFlag(std::shared_ptr<Switch>&);
	bool GetSwitchFlag();
	void Fire_MovetimeReset();
public:
	virtual ~Kanetuki();
	static Kanetuki::SP Create(Vec2& pos, bool = true);
	static Kanetuki::SP Create(Vec2& pos, std::shared_ptr<Switch>& swith, bool = true);
public:
};