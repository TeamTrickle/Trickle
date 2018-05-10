#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Water\water.h"
class Kanetuki : public GameObject, public TaskObject
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
public:

private:
	GameObject hitBace;
	//------------------
	//固定化されている処理
	//------------------
public:
	std::string taskName;
	virtual ~Kanetuki();
	typedef std::shared_ptr<Kanetuki> SP;
	static Kanetuki::SP Create(bool);
	Kanetuki();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize();		//初期化処理
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理
private:
	const int Fire_time_LIQUID = 70;	//加熱する時間 液体
	const int Fire_time_SOLID = 40;	    //加熱する時間 個体
	int Fire_movetime;					//燃やす時間を格納する

										//typedef std::vecor<Water*> WaterPool;
	std::vector<Water*> *water;

	//状態遷移
	void toSteam(Water*);		//水から水蒸気にする
public:
	void Create(Vec2, Vec2);	//座標値　当たり判定サイズ
	void SetWaterPool(std::vector<Water*> *);
};