#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Seihyouki : public Object
{
public:
	Seihyouki();
	~Seihyouki();
	void Create(Vec2, Vec2);		//座標値　当たり判定サイズ
	void CheckHit();
	void Motion();

	Object hitBace;
private:
	int movetime;
	const int movetime_ice = 20;	//氷にするまで・・・
};