#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Water;

class Kanetuki : public Object
{
public:
	Kanetuki();
	~Kanetuki();
	void Create(Vec2, Vec2);	//座標値　当たり判定サイズ
	void SetWaterPool(std::vector<Water*> *);
	void Update();
	Object hitBace;
private:
	const int Fire_time_LIQUID = 70;	//加熱する時間 液体
	const int Fire_time_SOLID = 40;	    //加熱する時間 個体
	int Fire_movetime;					//燃やす時間を格納する
	
	//typedef std::vecor<Water*> WaterPool;
	std::vector<Water*> *water;		

	//状態遷移
	void toSteam(Water*);		//水から水蒸気にする
};