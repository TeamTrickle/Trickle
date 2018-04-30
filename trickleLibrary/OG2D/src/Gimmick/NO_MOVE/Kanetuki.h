#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Water;

class Kanetuki : public Object
{
public:
	Kanetuki();
	~Kanetuki();
	bool Create(Vec2, Vec2);	//座標値　当たり判定サイズ
	void CheckHit();			//当たり判定のみする
	void Set_pointa();			//マネージャーからWaterだけを全て抜きとる
	Object hitBace;
private:
	bool Initital;						//初期化処理を1度しかしないために・・・
	const int Fire_time_LIQUID = 60;	//加熱する時間 液体
	const int Fire_time_SOLID = 30;	    //加熱する時間 個体
	int Fire_movetime;					//燃やす時間を格納する
	std::vector <Water*>w_vec;

	
};

//cm にアドレスを渡す
//Create()をする
//Initialize()をする