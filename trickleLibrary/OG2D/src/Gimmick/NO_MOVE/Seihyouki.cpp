#include "Seihyouki.h"
using namespace std;
Seihyouki::Seihyouki()
{

}
Seihyouki::~Seihyouki()
{

}
bool Seihyouki::Create(Vec2 pos, Vec2 scale)
{
	movetime = 0;
	hitBace.CreateObject(Cube, pos, scale, 0);
	return true;
}
void Seihyouki::Set_pointa()
{
	hitBace.CollisionProcess = [&](const Object& obj)
	{
		if (obj.objectTag == "Water")
		{
			w_vec.push_back(const_cast<Water*>(((Water*)&obj)));
		}
	};
}
void Seihyouki::Set_pointa(Water* w)
{
	w_vec.push_back(w);
}
void Seihyouki::CheckHit()	//動いている
{
	for (auto w : w_vec)
	{
		if (w->hit(hitBace))
		{
			switch (w->GetState())
			{
			case Water::State::GAS://ガスの場合
				movetime++;
				if (movetime >= movetime_ice)
				{
					w->SetState(Water::State::LIQUID);
					movetime = 0;
				}
				break;
			case Water::State::LIQUID://液体の場合
				movetime++;
				if (movetime >= movetime_ice)
				{
					w->SetState(Water::State::SOLID);
					movetime = 0;
				}
				break;
			case Water::State::SOLID://個体の場合
				break;
			}
		}
	}
};