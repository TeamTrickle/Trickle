#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Kanetuki : public Object
{
public:
	Kanetuki();
	~Kanetuki();
	void Create(Vec2,Vec2);		//座標値　当たり判定サイズ
	void CheckHit();			//当たり判定のみする
	void Motion();				//起動する
	Object hitBace;
private:
	const int Fire_time_LIQUID = 30;	//加熱する時間 液体
	const int Fire_time_SOLID = 60;	    //加熱する時間 個体
	int Fire_movetime;			//燃やす時間を格納する
};

//cm にアドレスを渡す
//Create()をする
//Initialize()をする