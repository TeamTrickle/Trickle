#include "Seihyouki.h"

const int Map_Size = 64;    //当たり判定矩形のサイズ
const int COLDMAX = 30;     //氷になるまでの時間
const int COLDSPPED = 2;    //製氷機のパワー

//☆☆☆☆//---------------------------------------------------------
Seihyouki::Seihyouki()
{

}
//☆☆☆☆//---------------------------------------------------------
Seihyouki::Seihyouki(Vec2 pos)
{
	Pos.push_back(pos);              //vectorに座標値を追加する
}
//☆☆☆☆//---------------------------------------------------------
Seihyouki::~Seihyouki()
{

}
//☆☆☆☆//---------------------------------------------------------
void Seihyouki::Initialize()
{
	coldCount = 0;                    //製氷機カウンタを0クリアする
	hitBace.CreateObject(Objform::Cube, Pos[0], Vec2(Map_Size, Map_Size), 0);                         //当たり判定矩形を生成する
	hitBace.objectTag = "Seihyouki";
	CheakHit();                       //当たり判定処理をする
}
//追加関数//---------------------------------------------------------
void Seihyouki::CheakHit()
{
	hitBace.CollisionProcess = [&](const Object& o_)
	{
		if (o_.objectTag == "Water")           //このオブジェクトは水であるか？
		{
			if (((Water&)o_).GetState() == Water::State::LIQUID)
			{
				coldCount += COLDSPPED;        //徐々に液体を凍らせていく
				if (coldCount >= COLDMAX)      //液体が氷になったら
				{
					((Water&)o_).SetState(Water::State::SOLID);         //stateを変更
					coldCount = 0;                                      //カウンタを元に戻す
				}
			}
		}
	};
}
//追加関数//---------------------------------------------------------
void Seihyouki::Input_Pos(Vec2 pos)
{
	Pos.push_back(pos);                //vectorに引数の座標値を追加する
}