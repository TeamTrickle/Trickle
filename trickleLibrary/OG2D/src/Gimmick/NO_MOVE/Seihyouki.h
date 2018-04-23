#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Seihyouki : public Object
{
public:
	Seihyouki();
	~Seihyouki();
	bool Create(Vec2, Vec2);		//座標値　当たり判定サイズ
	void CheckHit();				//当たり判定
	void Set_pointa();				//水の当たり判定を登録する
	Object hitBace;
private:
	bool Initital;					//1度初期化処理をしているかどうか・・・
	int movetime;					//氷にするまでの格納するフレーム数
	const int movetime_ice = 20;	//氷にするまで・・・
	std::vector<Water*> w_vec;		//水を格納するためのやつ
};