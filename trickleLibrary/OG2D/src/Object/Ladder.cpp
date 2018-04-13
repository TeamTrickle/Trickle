#include "Ladder.h"
const Vec2 IMAGE_SIZE(32, 32);			//画像サイズ
const Vec2 POS(100, 100);				//初期座標

Ladder::Ladder()
{
	objectTag = "Ladder";
	flag = false;
}
Ladder::~Ladder()
{

}
bool Ladder::Initialize()
{
	CreateObject(Objform::Cube, POS, IMAGE_SIZE, 0);
	return true;
}
void Ladder::Update()
{
	flag = CheakHit();
	if (flag)
	{
		std::cout << "梯子を渡れるようにします" << std::endl;
	}
}
void Ladder::Render()
{
	//map内での処理なのであまり意味がない
}
void Ladder::Finalize()
{

}
bool Ladder::CheakHit()
{
	Object::CollisionProcess = [&](const Object& o_)
	{
		if (o_.objectTag == "Player")
		{
			return true;
		}
		return false;
	};
	return false;
}