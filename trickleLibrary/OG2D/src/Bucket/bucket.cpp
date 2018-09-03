#include "Bucket\bucket.h"
#include "Water\water.h"
#include "Map\Map.h"
#include "Player\Player.h"
#include "Block\block.h"
#include "Gimmick/NO_MOVE/WeightSwitch.h"
Bucket::Bucket() {
	this->invi = 0;
}

Bucket::Bucket(Vec2& pos) {
	this->position = pos;
	this->invi = 0;
	this->mass = 1.0f;       //仮
	//サウンドのファイル名
	putsoundname = "bucket-put1.wav";
	dropsoundname = "spoil.wav";
	soundname = "water-drop3.wav";
	this->color = nullptr;
}

Bucket::~Bucket() {
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{

	}
}

bool Bucket::Initialize(Vec2& pos)
{
	this->position = pos;
	gravity = Vec2(0.0f, 0.0f);
	hold = false;
	this->capacity = 0;
	this->CreateObject(Objform::Cube, pos, Vec2(64.f, 64.f), 0.f);
	this->objectTag = "Bucket";
	//サウンドを連続して呼ばないためのフラッグ
	putsoundplay = true;

	//サウンドの生成　水をこぼす音
	soundD.create(dropsoundname, false);
	soundD.volume(1.0f);
	OGge->soundManager->SetSound(&soundD);

	//サウンドの生成 バケツを置く音
	soundP.create(putsoundname, false);
	soundP.volume(1.0f);
	OGge->soundManager->SetSound(&soundP);

	//サウンド生成　水がバケツにあたった音
	sound.create(soundname, false);

	tex.Create((std::string)"bucket.png");
	__super::Init((std::string)"bucket");
	__super::SetDrawOrder(0.5f);
	this->IsOutCheck = false;
	this->WaterOutTime = 0;
	this->WaterHitObj.CreateObject(Cube, pos, Vec2(64, 32), 0.f);
	return true;
}

void Bucket::UpDate() {
	if (this->invi > 0)
	{
		--this->invi;
	}
	if (hold)
	{
		//サウンドを再生するのを許可
		putsoundplay = true;
		gravity.y = 0.0f;
	}
	gravity.y += 5.0f;
	if (this->BucketWaterCreate())	//バケツから水を出す処理
	{
		if (!this->IsOutCheck)
		{
			auto player = OGge->GetTask<Player>("Player");
			player->SetMotion(Player::Motion::Spill);
			this->IsOutCheck = true;
		}
	}
	if (this->IsOutCheck)
	{
		this->WaterOutTime++;
		if (this->WaterOutTime > 10)
		{

			//水をこぼす音の再生
			soundD.play();

			auto water = Water::Create(Vec2(this->position.x + (this->Scale.x / 2) - 32.f, this->position.y - 20.f));
			water->SetSituation(Water::Situation::Normal);
			water->SetScale(Vec2(64, 64));
			water->SetWaterVolume(capacity);     //生成する水の量に、バケツに入っていた水の量を反映させる

			this->capacity = 0.f;
			//70カウント中は次の水を引き受けない
			this->invi = 70;
			auto tex = rm->GetTextureData((std::string)"waterTex");
			if (tex)
			{
				water->SetTexture(tex);
			}
			else
			{
				water->Kill();
			}
			if (this->color)
			{
				water->SetColor(*this->color);
				delete this->color;
				this->color = nullptr;
			}
			this->IsOutCheck = false;
			this->WaterOutTime = 0;
		}
	}
	//水が当たった時の処理
	this->WaterIsHitCheck();
	if (!hold)
	{
		CheckMove(gravity);
	}
	//バケツの重さの変化について
	//一滴の重さ
	if (capacity > 0.f && capacity < 1.0f)
	{
		this->mass = 1.5f;
	}
	//二滴の重さ
	if (capacity >= 1.0f)
	{
		this->mass = 2.0f;
	}
	//空の重さ
	if (capacity == 0.0f)
	{
		this->mass = 1.0f;
	}
}

void Bucket::Render2D() {
	Box2D draw(this->position, this->Scale);
	if (!this->hold)
	{
		draw.y += 2.0f;
	}
	draw.OffsetSize();
	Box2D src(GetSpriteCrop());
	if (this->color)
	{
		switch (*this->color)
		{
		case Paint::PaintColor::Blue:
			src.y += 768;
			break;
		case Paint::PaintColor::Red:
			src.y += 512;
			break;
		case Paint::PaintColor::Purple:
			src.y += 256;
			break;
		default:
			break;
		}
	}
	src.OffsetSize();
	tex.Rotate(this->angle);
	tex.Draw(draw, src);
	this->WaterHitObj.LineDraw();
}

bool Bucket::Finalize() {
	tex.Finalize();
	if (this->color)
	{
		delete this->color;
		this->color = nullptr;
	}
	return true;
}

Box2D Bucket::GetSpriteCrop() const {
	if (capacity > 0.f && capacity < 1.0f)
	{
		return BUCKET_WATER;
	}
	else if (capacity >= 1.0f)
	{
		return BUCKET_WATERMAX;
	}
	return BUCKET_NOTHING;
}

//-----------------------------------------------------------------------------------------------
//めり込まない処理
void Bucket::CheckMove(Vec2 &e_)
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

		if (isObjectCollided())
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

		if (isObjectCollided())
		{
			this->position.y = preY;
			auto Wswitch = OGge->GetTasks<WeightSwitch>("WeightSwitch");
			if (Wswitch != nullptr)
			{
				for (auto id = Wswitch->begin(); id != Wswitch->end(); ++id)
				{
					this->position.y += (*id)->SetSwitchUpPos();
				}
			}
			break;
		}
	}
}

bool Bucket::isObjectCollided() {
	bool hitMap = false;
	bool hitBlock = false;
	//テスト追加
	bool hitWswitch = false;
	auto map = OGge->GetTask<Map>("map");
	auto block = OGge->GetTask<Block>("block");
	//テスト追加
	auto Wswitch = OGge->GetTasks<WeightSwitch>("WeightSwitch");
	if (map) {
		hitMap = map->HitCheck(*this, 1);
		if (hitMap == true)
		{
			if (putsoundplay)    //サウンドを一回再生したかどうかの判断
			{
				soundP.play();
				putsoundplay = false;
			}
		}
	}
	if (block) {
		hitBlock = block->CubeHit(*this);
	}
	//テスト追加
	for (auto id = Wswitch->begin(); id != Wswitch->end(); ++id)
	{
		if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (this->CubeHit(*(*id)))
			{
				hitWswitch = true;
			}
		}
	}

	return hitMap || hitBlock || hitWswitch;
}

void Bucket::HoldCheck(bool flag)
{
	this->hold = flag;
}


bool Bucket::GetHold() const
{
	return this->hold;
}

bool Bucket::BucketWaterCreate()
{
	return this->hold && OGge->in->down(In::B3) && this->capacity > 0.f;
}

Bucket::SP Bucket::Create(Vec2& pos, bool flag_)
{
	auto to = Bucket::SP(new Bucket(pos));
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

void Bucket::WaterIsHitCheck()
{
	if (this->invi > 0 || this->capacity >= 1.0f)
	{
		return;
	}
	this->WaterHitObj.position = this->position;
	auto waters = OGge->GetTasks<Water>("water");
	for (int i = 0; i < (*waters).size(); ++i)
	{
		if (this->IsObjectDistanceCheck((*waters)[i]->position, (*waters)[i]->Scale))
		{
			if (this->WaterHitObj.hit(*(*waters)[i]))
			{
				float cap = (*waters)[i]->waterMove();
				if (cap > 0.0f)
				{

					if (this->color)
					{
						if (*this->color == Paint::PaintColor::Purple)
						{
							//紫なら色の変化を行わない
						}
						else if (*this->color == Paint::PaintColor::Blue && (*waters)[i]->GetColor() == Paint::PaintColor::Red)
						{
							//青と赤で紫へ
							if (this->color)
							{
								delete this->color;
							}
							this->color = new Paint::PaintColor;
							*this->color = Paint::PaintColor::Purple;
						}
						else if (*this->color == Paint::PaintColor::Red && (*waters)[i]->GetColor() == Paint::PaintColor::Blue)
						{
							//赤と青で紫へ
							if (this->color)
							{
								delete this->color;
							}
							this->color = new Paint::PaintColor;
							*this->color = Paint::PaintColor::Purple;
						}
						else
						{
							//それ以外はそのまま変化させる
							if (this->color)
							{
								delete this->color;
							}
							this->color = new Paint::PaintColor;
							*this->color = (*waters)[i]->GetColor();
						}
					}
					else
					{
						this->color = new Paint::PaintColor;
						*this->color = (*waters)[i]->GetColor();
					}
					sound.play();
					this->capacity += cap;
				}
			}
		}
	}
}