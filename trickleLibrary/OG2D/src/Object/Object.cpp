#include "Object.h"
GameObject::GameObject() {
	//各変数の初期化
	this->Gravity = false;
	this->angle = 0.f;
	this->objform = Objform::Non;
	this->mass = 0.f;
	this->Radius = { 1.0f,1.0f };
	this->isCheck = false;
}
GameObject::GameObject(const Objform& form, const Vec2& _posi, const  Vec2& _Sca, const float _ang)
{
	//各値をセットする
	this->objform = form;
	switch (objform)
	{
	case Objform::Cube:
		this->position = _posi;
		this->Scale = _Sca;
		break;
	case Objform::Ball:
		this->position = _posi;
		this->Scale = _Sca;
		break;
	}
	this->angle = _ang;
	this->HitCheck();
}
GameObject::~GameObject()
{
}
void GameObject::CreateObject(const Objform& form, const Vec2& _posi, const  Vec2& _Sca, const float _ang)
{
	//各値をセットする
	this->objform = form;
	switch (objform)
	{
	case Objform::Cube:
		this->position = _posi;
		this->Scale = _Sca;
		break;
	case Objform::Ball:
		this->position = _posi;
		this->Scale = _Sca;
		break;
	}
	this->angle = _ang;
	this->HitCheck();
}
bool GameObject::hit(GameObject& o)
{
	if (!this->isCheck || !o.isCheck)
	{
		return false;
	}
	switch (this->objform)
	{
	case Objform::Cube:			//自分が矩形の時
	{
		Vec2 ScaleSize = { this->Scale.x * this->Radius.x,this->Scale.y * this->Radius.y };
		//当たり判定を生成する
		this->collisionCube.hitBase = {
			this->position.x + ((this->Scale.x - ScaleSize.x) / 2),
			this->position.y + ((this->Scale.y - ScaleSize.y) / 2),
			ScaleSize.x + (this->position.x + ((this->Scale.x - ScaleSize.x) / 2)),
			ScaleSize.y + (this->position.y + ((this->Scale.y - ScaleSize.y) / 2))
		};
		//回転値を適用させる
		this->collisionCube.Rotate(this->angle);
		switch (o.objform)
		{
		case Objform::Cube:		//相手が矩形の時
		{
			Vec2 ScaleSize_o = { o.Scale.x * o.Radius.x,o.Scale.y * o.Radius.y };
			//位置とサイズから当たり判定を生成する
			o.collisionCube.hitBase = {
				o.position.x + ((o.Scale.x - ScaleSize_o.x) / 2),
				o.position.y + ((o.Scale.y - ScaleSize_o.y) / 2),
				ScaleSize_o.x + (o.position.x + ((o.Scale.x - ScaleSize_o.x) / 2)),
				ScaleSize_o.y + (o.position.y + ((o.Scale.y - ScaleSize_o.y) / 2))
			};
			//回転値を適用させる
			o.collisionCube.Rotate(o.angle);
			//Collision内の判定を使用してその結果を返す
			return this->collisionCube.hitBox(o.collisionCube);
			break;
		}
		case Objform::Ball:		//相手が円の時
		{
			//位置とサイズから当たり判定を生成する
			o.collisionBall.hitBase = {
				o.Scale.x,
				o.position.x,
				o.position.y };
			//Collision内の判定を使用してその結果を返す
			return this->collisionCube.hitCircle(o.collisionBall);
			break;
		}
		}
	}
	break;
	case Objform::Ball:			//自分が円の時
	{
		//位置とサイズから当たり判定を生成する
		this->collisionBall.hitBase = {
			this->Scale.x,
			this->position.x,
			this->position.y };
		switch (o.objform)
		{
		case Objform::Cube:		//相手が矩形の時
		{
			Vec2 ScaleSize_o = { o.Scale.x * o.Radius.x,o.Scale.y * o.Radius.y };
			//位置とサイズから当たり判定を生成する
			o.collisionCube.hitBase = {
				o.position.x + ((o.Scale.x - ScaleSize_o.x) / 2),
				o.position.y + ((o.Scale.y - ScaleSize_o.y) / 2),
				ScaleSize_o.x + (o.position.x + ((o.Scale.x - ScaleSize_o.x) / 2)),
				ScaleSize_o.y + (o.position.y + ((o.Scale.y - ScaleSize_o.y) / 2))
			};
			o.collisionCube.Rotate(o.angle);
			//Collision内の判定を使用してその結果を返す
			return this->collisionBall.hitBox(o.collisionCube);
			break;
		}
		case Objform::Ball:		//相手が円の時
		{
			//位置とサイズから当たり判定を生成する
			o.collisionBall.hitBase = {
				o.Scale.x,
				o.position.x,
				o.position.y };
			//Collision内の判定を使用してその結果を返す
			return this->collisionBall.hitCircle(o.collisionBall);
			break;
		}
		}
		break;
	}
	}
	return false;
}
bool GameObject::CubeHit(GameObject &o)
{
	if (this->objform != Objform::Cube || o.objform != Objform::Cube)
	{
		return false;
	}
	Vec2 ScaleSize = { this->Scale.x * this->Radius.x,this->Scale.y * this->Radius.y };
	//当たり判定を生成する
	this->collisionCube.hitBase = {
		this->position.x + ((this->Scale.x - ScaleSize.x) / 2),
		this->position.y + ((this->Scale.y - ScaleSize.y) / 2),
		ScaleSize.x + (this->position.x + ((this->Scale.x - ScaleSize.x) / 2)),
		ScaleSize.y + (this->position.y + ((this->Scale.y - ScaleSize.y) / 2))
	};
	Vec2 ScaleSize_o = { o.Scale.x * o.Radius.x,o.Scale.y * o.Radius.y };
	//位置とサイズから当たり判定を生成する
	o.collisionCube.hitBase = {
		o.position.x + ((o.Scale.x - ScaleSize_o.x) / 2),
		o.position.y + ((o.Scale.y - ScaleSize_o.y) / 2),
		ScaleSize_o.x + (o.position.x + ((o.Scale.x - ScaleSize_o.x) / 2)),
		ScaleSize_o.y + (o.position.y + ((o.Scale.y - ScaleSize_o.y) / 2))
	};
	if (this->collisionCube.hitBase.x < o.collisionCube.hitBase.w &&
		this->collisionCube.hitBase.w > o.collisionCube.hitBase.x &&
		this->collisionCube.hitBase.y < o.collisionCube.hitBase.h &&
		this->collisionCube.hitBase.h > o.collisionCube.hitBase.y)
	{
		return true;
	}
	return false;
}

void GameObject::LineDraw()
{
#if(_DEBUG)
	switch (this->objform)
	{
	case Objform::Cube:		//自分が矩形の時
	{
		Vec2 ScaleSize = { this->Scale.x * this->Radius.x,this->Scale.y * this->Radius.y };
		//当たり判定を生成する
		this->collisionCube.hitBase = {
			this->position.x + ((this->Scale.x - ScaleSize.x) / 2),
			this->position.y + ((this->Scale.y - ScaleSize.y) / 2),
			ScaleSize.x + (this->position.x + ((this->Scale.x - ScaleSize.x) / 2)),
			ScaleSize.y + (this->position.y + ((this->Scale.y - ScaleSize.y) / 2))
		};
		//回転を適用する
		this->collisionCube.Rotate(this->angle);
		//Collision内で使用しているVec2配列型に変更
		Vec2 _v[4] = {
			{ this->collisionCube.hitBase.x,this->collisionCube.hitBase.y },
		{ this->collisionCube.hitBase.w - 1,this->collisionCube.hitBase.y },
		{ this->collisionCube.hitBase.w - 1,this->collisionCube.hitBase.h - 1 },
		{ this->collisionCube.hitBase.x,this->collisionCube.hitBase.h - 1 }
		};
		//その値を回転を適用させた値に変更する
		OG::_Rotate(this->collisionCube.Rotate(), _v);
		//４つの頂点を線で結ぶ
		OG::LineHitDraw(_v);
		break;
	}
	case Objform::Ball:
		break;
	case Objform::Non:
		break;
	}
#endif
}

void GameObject::HitCheck(bool flag)
{
	this->isCheck = flag;
}

bool GameObject::IsObjectDistanceCheck(const Vec2& pos, const Vec2& size)
{
	float maxSize[2];
	if (this->Scale.x > this->Scale.y)
	{
		maxSize[0] = this->Scale.x;
	}
	else
	{
		maxSize[0] = this->Scale.y;
	}
	if (size.x > size.y)
	{
		maxSize[1] = size.x;
	}
	else
	{
		maxSize[1] = size.y;
	}
	if (this->position.x - maxSize[0] < pos.x + maxSize[1] &&
		this->position.y - maxSize[0] < pos.y + maxSize[1] &&
		this->position.x + maxSize[0] * 2 > pos.x &&
		this->position.y + maxSize[0] * 2 > pos.y)
	{
		return true;
	}
	return false;
}

void GameObject::LineDistanceDraw()
{
	float maxSize;
	if (this->Scale.x > this->Scale.y)
	{
		maxSize = this->Scale.x;
	}
	else
	{
		maxSize = this->Scale.y;
	}
	Box2D d(
		this->position.x - maxSize,
		this->position.y - maxSize,
		this->position.x + maxSize * 2,
		this->position.y + maxSize * 2);
	OG::LineHitDraw(&d);
}

void GameObject::Move()
{

}

void GameObject::Friction()
{

}