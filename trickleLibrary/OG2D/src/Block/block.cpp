#include "Block/block.h"   //変更した
#include "Player\Player.h"
#include "Map\Map.h"
#include "Effect\Effect.h"
Block::Block() {
	this->Cnt = 0;
}

Block::Block(Vec2& pos) {
	this->position = pos;
}

Block::~Block() {
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{

	}
}

bool Block::Initialize(Vec2& pos) {
	//speed = 0.0f;
	//横移動初期値
	speed.x = 0.0f;
	speed.y = 0.0f;    //不要
					   //重力初期値
	gravity.x = 0.0f;  //不要
	gravity.y = 0.0f;

	//プレイヤとの当たり判定フラッグ　使わなくなった
	plhitH = false;
	plhitF = false;
	plhitL = false;
	plhitR = false;

	GameObject::CreateObject(Objform::Cube, pos, Vec2(160.f, 160.f), 0.f);       //オブジェクトの生成
	GameObject::objectTag = "Block";
	/*GameObject::CollisionProcess = [&](const GameObject& o_) {

	};*/

	tex.Create((std::string)"block.png");
	__super::Init((std::string)"block");
	return true;
}

void Block::UpDate() {
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

	std::cout << "this->GameObject=" << position.x << "," << position.y << "," << Scale.x << "," << Scale.y << std::endl;
	std::cout << "headBase=" << headBase.position.x << "," << headBase.position.y << "," << headBase.Scale.x << "," << headBase.Scale.y << std::endl;
	std::cout << "footBase=" << footBase.position.x << "," << footBase.position.y << "," << footBase.Scale.x << "," << footBase.Scale.y << std::endl;
	std::cout << "rightBase=" << rightBase.position.x << "," << rightBase.position.y << "," << rightBase.Scale.x << "," << rightBase.Scale.y << std::endl;
	std::cout << "leftBase=" << leftBase.position.x << "," << leftBase.position.y << "," << leftBase.Scale.x << "," << leftBase.Scale.y << std::endl;
	*/
	auto p = OGge->GetTask<Player>("Player");
	if (p)
	{
		//this->PlCheckHit(*p);
		if (plhit)
		{
			if (p->position.x < this->position.x)
			{
				//speed.x = 5.0f;はテスト用に設定
				//speed.x = 5.0f;
				CheckMove(speed);
			}
			if (p->position.x > this->position.x)
			{
				//speed.x = -5.0f;
				CheckMove(speed);
			}
		}
	}
	gravity.y = 4.0f;
	Vec2 move = this->gravity;
	CheckMove(move);
}

void Block::Render2D() {
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	Box2D src(0, 0, 256, 256);
	src.OffsetSize();
	tex.Draw(draw, src);
}

bool Block::Finalize() {
	tex.Finalize();
	return true;
}

Vec2 Block::GetMove(Vec2& move)       //moveにプレイヤから受け取る移動量を入れる
{
	speed.x = move.x;
	return speed;
}
//めり込んだ値を返す処理
Vec2 Block::BackMove()
{
	return backmove;
}


//プレイヤとの当たり判定について 使わなくなった
//--------------------------------------------------------------------------------------------------------------
void Block::PlCheckHitF(GameObject &p)
{
	plhitF = footBase.hit(p);
}
void Block::PlCheckHitH(GameObject &p)
{
	plhitH = headBase.hit(p);
}
void Block::PlCheckHitR(GameObject &p)
{
	plhitR = rightBase.hit(p);
}
void Block::PlCheckHitL(GameObject &p)
{
	plhitL = leftBase.hit(p);
}

void Block::PlCheckHit(GameObject &p)
{
	plhit = this->hit(p);
}

//-----------------------------------------------------------------------------------------------
//めり込まない処理
void Block::CheckMove(Vec2 &e_)
{
	float dir = 0;
	
	//x軸について
	while (e_.x != 0.0f)
	{
		float preX = this->position.x;

		if (e_.x >= 1.0f)
		{
			this->position.x += 1.0f;
			e_.x -= 1.0f;
			dir += 1.f;
		}
		else if (e_.x <= -1.0f)
		{
			this->position.x -= 1.0f;
			e_.x += 1.0f;
			dir -= 1.f;
		}
		else
		{
			this->position.x += e_.x;
			e_.x = 0.0f;
			dir += e_.x;
		}
		this->Cnt++;
		if (isCollideSomething())
		{
			backmove.x = position.x - preX;
			this->position.x = preX;
			Cnt = 0;
			break;
		}
		else
		{
			//エフェクト表示処理
			if (this->footCheck())
			{
				if (this->Cnt > 5)
				{
					if (dir > 0.f)
					{
						auto effect = Effect::Create(
							Vec2(this->foot.position.x - 32.f, this->position.y + this->Scale.y - 32.f),
							Vec2(64, 64),
							Vec2(768, 768),
							1,
							50);
						effect->SetTexture(rm->GetTextureData((std::string)"sandsmoke"));
						effect->Set(effect->position, Vec2(effect->position.x, effect->position.y - 128.f));
						effect->SetMode(Effect::Mode::Decrease);
					}
					else if (dir < 0.f)
					{
						auto effect = Effect::Create(
							Vec2(this->foot.position.x + this->foot.Scale.x - 32.f, this->position.y + this->Scale.y - 32.f),
							Vec2(64, 64),
							Vec2(768, 768),
							1,
							50);
						effect->SetTexture(rm->GetTextureData((std::string)"sandsmoke"));
						effect->Set(effect->position, Vec2(effect->position.x, effect->position.y - 128.f));
						effect->SetMode(Effect::Mode::Decrease);
					}
					this->Cnt = 0;
				}
			}
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

		if (isCollideSomething())
		{
			backmove.y = position.y - preY;
			this->position.y = preY;
			break;
		}
	}
}


bool Block::isCollideSomething() 
{
	auto map = OGge->GetTask<Map>("map");
	if (!map) {
		return false;
	}
	auto buckets = OGge->GetTasks<Bucket>("bucket");
	for (auto id = buckets->begin(); id != buckets->end(); ++id)
	{
		if (!(*id)->GetHold())
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->hit(*(*id)))
				{
					return true;
				}
			}
		}
	}

	return map->MapHitCheck(*this);
}

bool Block::footCheck()
{
	foot.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (map)
	{
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (foot.IsObjectDistanceCheck(map->hitBase[y][x].position, map->hitBase[y][x].Scale))
				{
					if (map->hitBase[y][x].objectTag == "Floor")
					{
						if (foot.hit(map->hitBase[y][x]))
						{
							return true;
						}
					}
				}
			}
		}
	}
	auto buckets = OGge->GetTasks<Bucket>("bucket");
	for (auto id = buckets->begin(); id != buckets->end(); ++id)
	{
		if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (this->hit(*(*id)))
			{
				return true;
			}
		}
	}
	return false;
}

Block::SP Block::Create(Vec2& pos, bool flag_)
{
	auto to = Block::SP(new Block(pos));
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}