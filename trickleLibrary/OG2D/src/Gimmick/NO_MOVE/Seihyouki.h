#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Seihyouki : public Object
{
public:
	Seihyouki();
	~Seihyouki();
	void Create(Vec2, Vec2);		//座標値　当たり判定サイズ
	Object hitBace;
	void UpDate();
	void toIce(Water*);				//氷にする
	void SetWaterPool(std::vector<Water*>*);			//データを渡す関数
private:
	int movetime;					//氷にするまでの格納するフレーム数
	const int movetime_ice = 20;	//氷にするまで・・・
	std::vector<Water*> *water;		//Vectorポインタ
};