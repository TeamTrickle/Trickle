#include "Collision.h"
//--------------------------------------------------
//@:Collisionclass									
//--------------------------------------------------
//’·•ûŒ`~’·•ûŒ`
bool CollisionBox::hitBox(CollisionBox b)
{
	//’¸“_î•ñ‚ÌƒZƒbƒg
	Vec2 _ver[4] = {
		{ b.hitBase.x,b.hitBase.y },
	{ b.hitBase.w - 1,b.hitBase.y },
	{ b.hitBase.w - 1,b.hitBase.h },
	{ b.hitBase.x,b.hitBase.h }
	};
	Vec2 _v[4] = {
		{ hitBase.x,hitBase.y },
	{ hitBase.w - 1,hitBase.y },
	{ hitBase.w - 1,hitBase.h },
	{ hitBase.x,hitBase.h }
	};
	//‰ñ“]‚Ì“K—p
	OG::_Rotate(angle, _v);
	OG::_Rotate(b.angle, _ver);
	//‚Ç‚¿‚ç‚©‚Ì”ÍˆÍ“à‚É‘Šè‚Ì’¸“_‚ª‘¶İ‚·‚éê‡TRUE‚ğ•Ô‚·
	for (int i = 0; i < 4; ++i) {
		if ((((_v[1].x - _v[0].x)*(_ver[i].y - _v[0].y)) - ((_ver[i].x - _v[0].x)*(_v[1].y - _v[0].y))) >= 0 &&
			(((_v[2].x - _v[1].x)*(_ver[i].y - _v[1].y)) - ((_ver[i].x - _v[1].x)*(_v[2].y - _v[1].y))) >= 0 &&
			(((_v[3].x - _v[2].x)*(_ver[i].y - _v[2].y)) - ((_ver[i].x - _v[2].x)*(_v[3].y - _v[2].y))) >= 0 &&
			(((_v[0].x - _v[3].x)*(_ver[i].y - _v[3].y)) - ((_ver[i].x - _v[3].x)*(_v[0].y - _v[3].y))) >= 0)
		{
			return true;
		}
	}
	for (int i = 0; i < 4; ++i) {
		if ((((_ver[1].x - _ver[0].x)*(_v[i].y - _ver[0].y)) - ((_v[i].x - _ver[0].x)*(_ver[1].y - _ver[0].y))) >= 0 &&
			(((_ver[2].x - _ver[1].x)*(_v[i].y - _ver[1].y)) - ((_v[i].x - _ver[1].x)*(_ver[2].y - _ver[1].y))) >= 0 &&
			(((_ver[3].x - _ver[2].x)*(_v[i].y - _ver[2].y)) - ((_v[i].x - _ver[2].x)*(_ver[3].y - _ver[2].y))) >= 0 &&
			(((_ver[0].x - _ver[3].x)*(_v[i].y - _ver[3].y)) - ((_v[i].x - _ver[3].x)*(_ver[0].y - _ver[3].y))) >= 0)
		{
			return true;
		}
	}
	return false;
}
//’·•ûŒ`~‰~
bool CollisionBox::hitCircle(CollisionCircle b)
{
	//’¸“_î•ñ‚ÌƒZƒbƒg
	Vec2 _ver[1] = {
		{ b.hitBase.CenterX,b.hitBase.CenterY }
	};
	Vec2 _v[4] = {
		{ hitBase.x,hitBase.y },
	{ hitBase.w - 1,hitBase.y },
	{ hitBase.w - 1,hitBase.h },
	{ hitBase.x,hitBase.h }
	};
	//BoxŒ^‚Ì‰ñ“]‚Ì“K—p
	OG::_Rotate(angle, _v);
	//‰~‚Ì’†‚É’¸“_‚ª‘¶İ‚·‚éê‡TRUE‚ğ•Ô‚·
	if ((((_v[1].x - _v[0].x)*(_ver[0].y - _v[0].y)) - ((_ver[0].x - _v[0].x)*(_v[1].y - _v[0].y))) <= b.hitBase.r*b.hitBase.r &&
		(((_v[2].x - _v[1].x)*(_ver[0].y - _v[1].y)) - ((_ver[0].x - _v[1].x)*(_v[2].y - _v[1].y))) <= b.hitBase.r*b.hitBase.r &&
		(((_v[3].x - _v[2].x)*(_ver[0].y - _v[2].y)) - ((_ver[0].x - _v[2].x)*(_v[3].y - _v[2].y))) <= b.hitBase.r*b.hitBase.r &&
		(((_v[0].x - _v[3].x)*(_ver[0].y - _v[3].y)) - ((_ver[0].x - _v[3].x)*(_v[0].y - _v[3].y))) <= b.hitBase.r*b.hitBase.r)
	{
		return true;
	}
	//‰~‚Ì’†‚Éü•ª‚ª‘¶İ‚·‚éê‡TRUE‚ğ•Ô‚·
	for (int i = 0; i<4; i++) {
		if (OG::get_distance(_ver[0].x, _ver[0].y, _v[i].x, _v[i].y, _v[(i + 1) % 4].x, _v[(i + 1) % 4].y)<b.hitBase.r)
			return true;
	}
	return false;
}
//‰~~’·•ûŒ`
bool CollisionCircle::hitBox(CollisionBox b)
{
	//’¸“_î•ñ‚ÌƒZƒbƒg
	Vec2 _ver[1] = {
		{ hitBase.CenterX,hitBase.CenterY }
	};
	Vec2 _v[4] = {
		{ b.hitBase.x,b.hitBase.y },
	{ b.hitBase.w - 1,b.hitBase.y },
	{ b.hitBase.w - 1,b.hitBase.h },
	{ b.hitBase.x,b.hitBase.h }
	};
	//BoxŒ^‚Ì‰ñ“]‚Ì“K—p
	OG::_Rotate(b.angle, _v);
	//‰~‚Ì’†‚É’¸“_‚ª‘¶İ‚·‚éê‡TRUE‚ğ•Ô‚·
	if ((((_v[1].x - _v[0].x)*(_ver[0].y - _v[0].y)) - ((_ver[0].x - _v[0].x)*(_v[1].y - _v[0].y))) <= hitBase.r*hitBase.r &&
		(((_v[2].x - _v[1].x)*(_ver[0].y - _v[1].y)) - ((_ver[0].x - _v[1].x)*(_v[2].y - _v[1].y))) <= hitBase.r*hitBase.r &&
		(((_v[3].x - _v[2].x)*(_ver[0].y - _v[2].y)) - ((_ver[0].x - _v[2].x)*(_v[3].y - _v[2].y))) <= hitBase.r*hitBase.r &&
		(((_v[0].x - _v[3].x)*(_ver[0].y - _v[3].y)) - ((_ver[0].x - _v[3].x)*(_v[0].y - _v[3].y))) <= hitBase.r*hitBase.r)
	{
		return true;
	}
	//‰~‚Ì’†‚Éü•ª‚ª‘¶İ‚·‚éê‡TRUE‚ğ•Ô‚·
	for (int i = 0; i<4; i++) {
		if (OG::get_distance(_ver[0].x, _ver[0].y, _v[i].x, _v[i].y, _v[(i + 1) % 4].x, _v[(i + 1) % 4].y)<hitBase.r)
			return true;
	}
	return false;
}
//‰~~‰~
bool CollisionCircle::hitCircle(CollisionCircle b)
{
	//‰~‚Ì”ÍˆÍ“à‚É‘Šè‚Ì‰~‚Ì”ÍˆÍ‚ª‘¶İ‚·‚éê‡TRUE‚ğ•Ô‚·
	if (((b.hitBase.CenterX - this->hitBase.CenterX)*
		(b.hitBase.CenterX - this->hitBase.CenterX)) +
		((b.hitBase.CenterY - this->hitBase.CenterY)*
		(b.hitBase.CenterY - this->hitBase.CenterY)) <=
			(b.hitBase.r + this->hitBase.r)*(b.hitBase.r + this->hitBase.r))
	{
		return true;
	}
	return false;
}
//•`‰æŠm”F—p(‘½•ªg‚í‚È‚¢)
void CollisionBox::hitdraw() {

}
void CollisionBox::Rotate(float _angle) {
	//‰ñ“]‚Ì’l‚ğŠi”[
	this->angle = _angle;
}