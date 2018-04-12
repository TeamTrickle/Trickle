#include "Block/block.h"   //変更した

Block::Block(){
}

Block::Block(Vec2 pos) {
	this->position = pos;
}

Block::~Block() {

}

bool Block::Initialize(Vec2 pos) {
	//speed = 0.0f;
	//横移動初期値
	speed.x = 0.0f;
	speed.y = 0.0f;    //不要
	//重力初期値
	gravity.x = 0.0f;  //不要
	gravity.y = 0.0f;

	//プレイヤとの当たり判定フラッグ
	plhitH = false;
	plhitF = false;
	plhitL = false;
	plhitR = false;
	//マップとの当たり判定フラッグ
	maphitH = false;
	maphitF = false;
	maphitL = false;
	maphitR = false;

	Object::CreateObject(Objform::Cube, pos, Vec2(128.f, 128.f), 0.f);       //オブジェクトの生成
	Object::objectTag = "Block";
	Object::CollisionProcess = [&](const Object& o_) {

	};

	//当たり判定用オブジェクトの生成
	CreateHead();
	CreateFoot();
	CreateLeft();
	CreateRight();

	tex.TextureCreate("Collision.png");

	return true;
}

void Block::Update(Map &map, Block &block) {
	//追加した----------------------------------------------------------------------------
	footBase.position = Vec2(this->position.x, this->position.y + this->Scale.y);
	headBase.position = Vec2(this->position.x, this->position.y - 1.f);
	leftBase.position = Vec2(this->position.x - 1.f, this->position.y);
	rightBase.position = Vec2(this->position.x + this->Scale.x, this->position.y);
	//------------------------------------------------------------------------------------

	//現在の状態確認用
	/*if (maphitF)
	{
		std::cout << "足下接触" << std::endl;
	}
	if (maphitH)
	{
		std::cout << "頭上接触" << std::endl;

	}
	if (maphitL)
	{
		std::cout << "左側接触" << std::endl;

	}
	if (maphitR)
	{
		std::cout << "右側接触" << std::endl;
	}

	std::cout << "this->Object=" << position.x << "," << position.y << "," << Scale.x << "," << Scale.y << std::endl;
	std::cout << "headBase=" << headBase.position.x << "," << headBase.position.y << "," << headBase.Scale.x << "," << headBase.Scale.y << std::endl;
	std::cout << "footBase=" << footBase.position.x << "," << footBase.position.y << "," << footBase.Scale.x << "," << footBase.Scale.y << std::endl;
	std::cout << "rightBase=" << rightBase.position.x << "," << rightBase.position.y << "," << rightBase.Scale.x << "," << rightBase.Scale.y << std::endl;
	std::cout << "leftBase=" << leftBase.position.x << "," << leftBase.position.y << "," << leftBase.Scale.x << "," << leftBase.Scale.y << std::endl;
	*/

	//マップにめり込まない処理実装
//	if (plhitL)
//	{
//		if (Input::KeyInputOn(Input::RIGHT))
//		{
//			speed.x += 5.0f;
//			CheckMove(speed, map, block);
//		}
//	}
//	if (plhitR)
//	{
//		if (Input::KeyInputOn(Input::LEFT))
//		{
//			speed.x -= 5.0f;
//			CheckMove(speed, map, block);
//		}
//	}
//		gravity.y = 4.0f;
//		CheckMove(gravity, map, block);
}

void Block::Render() {
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	Box2D src(0,0,128,128);
	src.OffsetSize();
	tex.Draw(draw, src);
}

void Block::Finalize() {
	tex.Finalize();
}

void Block::SetParent(Object* o_) {
	parent = o_;
}

bool Block::HasParent() const {
	return parent != nullptr;
}

//マップとの当たり判定について
//---------------------------------------------------------------------------------------------------
void Block::CreateHead()
{
	headBase.CreateObject(Cube, Vec2(this->position.x, this->position.y + this->Scale.y), 
		Vec2(this->Scale.x, 1.0f), 0.0f);
	headBase.objectTag = "BlockHead";
}
void Block::CreateFoot()
{
	footBase.CreateObject(Cube, Vec2(this->position.x, this->position.y - 1.f),
		Vec2(this->Scale.x , 1.0f), 0.0f);
	footBase.objectTag = "BlockFoot";
}
void Block::CreateLeft()
{
	leftBase.CreateObject(Cube, Vec2(this->position.x - 1.f,
		this->position.y), Vec2(1.0f, this->Scale.y), 0.0f);
	leftBase.objectTag = "BlockLeft";
}
void Block::CreateRight()
{
	rightBase.CreateObject(Cube, Vec2(this->position.x + this->Scale.x, this->position.y),
		Vec2(1.0f, this->Scale.y), 0.0f);
	rightBase.objectTag = "BlockRight";
}


//プレイヤとの当たり判定について
//--------------------------------------------------------------------------------------------------------------
void Block::PlCheckHitF(Object &p)
{
	plhitF = footBase.hit(p);
}
void Block::PlCheckHitH(Object &p)
{
	plhitH = headBase.hit(p);
}
void Block::PlCheckHitR(Object &p)
{
	plhitR = rightBase.hit(p);
}
void Block::PlCheckHitL(Object &p)
{
	plhitL = leftBase.hit(p);
}

//-----------------------------------------------------------------------------------------------
//めり込まない処理
void Block::CheckMove(Vec2 &e_, Map &map, Block &block)
{
	//x軸について
	while (e_.x != 0.0f)
	{
		float preX = this->position.x;

		if (e_.x >= 1.0f)
		{
			this->position.x += 1.0f;
			e_.x -= 1.0f;
		}
		else if (e_.x <= -1.0f)
		{
			this->position.x -= 1.0f;
			e_.x += 1.0f;
		}
		else
		{
			this->position.x += e_.x;
			e_.x = 0.0f;
		}

		if (map.MapHitCheck(block))
		{
			this->position.x = preX;
			break;
		}
	}
	//y軸について
	while (e_.y != 0.0f)
	{
		float preY = this->position.y;

		if (e_.y >= 1.0f)
		{
			this->position.y += 1.0f;
			e_.y -= 1.0f;
		}
		else if (e_.y <= -1.0f)
		{
			this->position.y -= 1.0f;
			e_.y += 1.0f;
		}
		else
		{
			this->position.y += e_.y;
			e_.y = 0.0f;
		}

		if (map.MapHitCheck(block))
		{
			this->position.y = preY;
			break;
		}
	}
}
