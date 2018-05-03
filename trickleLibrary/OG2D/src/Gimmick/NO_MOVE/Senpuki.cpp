#include "Senpuki.h"
using namespace std;


Fan::Fan()
{

}
Fan::Fan(Vec2 pos)
{
	position = pos;
}
Fan::~Fan()
{

}
void Fan::Initialize(Vec2 pos, float r, Fan::Dir d, bool activ) 
{
	//初期座標の設置
	position = pos;
	//オブジェクトタグの設定
	objectTag = "Fan";
	//範囲の設定
	range = r;
	//方向の指定
	dir = d;
	//0 true 1 false
	active = activ;

	//方向によって範囲の設定を変化させる
	if (dir == Fan::Dir::LEFT) 
	{
		//これだけ分からない
		CreateObject(Cube, Vec2(position.x - 64.0f*range, position.y), Vec2(64.0f * range, 64.0f), 0.0f);
		//移動Moveの設定
		movePos = -1;
	}
	else 
	{
		CreateObject(Cube, Vec2(position.x + 64.0f*range, position.y), Vec2(64.0f*range, 64.0f), 0.0f);
		movePos = 1;
	}

	//ラムダ式当たり判定
	Object::CollisionProcess = [&](const Object& o_) 
	{
		//trueになっているなら・・・
		if (active) 
		{//水と接触をしたら・・・
			if (o_.objectTag == "Water") 
			{//水か気体なら・・・
				if (((Water&)o_).GetSituation() == Water::Situation::Normal && ((Water&)o_).GetState() == Water::State::GAS) 
				{//移動MoveによってX座標を変化させる
					const_cast<Object&>(o_).position.x += movePos;
				}
			}
		}
	};
}
void Fan::AddSwitch(Switch* swit) 
{
	//
	switches.push_back(swit);
}
void Fan::ChangeState()
{
	//現時点でのフラグを逆転させる
	active = !active;
}
void Fan::Finalize() 
{
	switches.clear();
	image.Finalize();
}
void Fan::Render(){}