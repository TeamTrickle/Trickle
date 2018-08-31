#include "water.h"
#include "Map\Map.h"
#include "Block\block.h"
#include "Player\Player.h"
#include "Effect\Effect.h"
#include "Gimmick\NO_MOVE\Door.h"
#include "Gimmick/NO_MOVE/WeightSwitch.h"
//#include "Paint\Paint.h"
Water::Water(const Vec2& pos)
	:maxFall(15.f), gravity((9.8f / 60.f / 60.f*32.f) * 5), finSpeed(1.0f), rainTime(180)
{
	//タグ設定
	this->objectTag = "water";
	//描画最大最小サイズ
	this->minSize = { 0,0 };
	this->maxSize = { 64,64 };
	//経過時間初期化
	this->setTime = 0;
	//オブジェクトの生成
	CreateObject(Objform::Cube, pos, this->minSize, 0.f);
	//初期ステータスの設定
	this->nowSituation = Water::Situation::Newfrom;
	this->currentState = Water::State::LIQUID;
	this->preState = Water::State::LIQUID;
	//初期保持水量
	this->volume = 0.5f;
	//無敵時間初期化
	this->invi = 0;
	//カラー値の初期化
	this->color_a = { 1,1,1,1 };
	//移動値の初期化
	this->move = { 0,0 };
	//経過時間初期化
	this->nowTime = 0;
	//現在カラーを設定
	this->color = Paint::PaintColor::Normal;
	//IDを設定
	auto waters = OGge->GetTasks<Water>("water");
	int i = 0;
	auto ids = waters->begin();
	while (ids != waters->end())
	{
		if ((*ids)->id == i)
		{
			++i;
			ids = waters->begin();
		}
		else
		{
			++ids;
		}
	}
	this->id = i;
	//サウンドのファイル名設定
	soundname = "water-drop3.wav";
	//所持状態の初期化
	this->hold = false;
	//当たり判定を制限
	this->Radius = { 0.5f,1.f };
	//左右判定を初期化
	this->left = nullptr;
	this->right = nullptr;
	//タグの指定
	__super::Init((std::string)"water");
	//描画優先度の設定
	__super::SetDrawOrder(0.2f);
	//重さ設定仮
	if (this->volume < 1.0f)
	{
		this->mass = 0.5f;
	}
	else if(this->volume>=1.0f)
	{
		this->mass = 1.0f;
	}
	//カウンター初期化
	this->iceCnt = 0;
	this->fireCnt = 0;
}

Water::~Water()
{
	if (this->left)
	{
		delete this->left;
		this->left = nullptr;
	}
	if (this->right)
	{
		delete this->right;
		this->right = nullptr;
	}
}


bool Water::Initialize()
{
	soundplay = true;
	sound.create(soundname, false);

	return true;
}

void Water::UpDate()
{
	if (this->invi > 0)
	{
		this->invi--;
	}
	this->CheckState();
	switch (this->currentState) {
	case Water::State::LIQUID:
		this->objectTag = "Water";
		//水処理
		switch (this->nowSituation)
		{
		case Water::Situation::Newfrom:
			this->nowSituation = Water::UpNewform();
			break;
		case Water::Situation::Normal:
			this->nowSituation = Water::UpNormal();
			this->nowMove = this->move;
			this->MoveWATERCheck(this->nowMove);
			break;
		case Water::Situation::Deleteform:
			this->nowSituation = Water::UpDeleteform();
			break;
		case Water::Situation::CreaDelete:
			this->Kill();
			soundplay = true;
			break;
		}
		break;
	case Water::State::GAS:
		switch (this->nowSituation)
		{
		case Water::Situation::Normal:
			//水蒸気処理
			if (!this->HeadCheck((std::string)"Floor"))
			{
				this->move.y = -3.0f;
				this->nowTime = 0;
			}
			else
			{
				this->move.y = 0;
				if (this->GetMove().x == 0 && this->GetMove().y == 0)
				{
					this->nowTime++;
				}
			}
			//静止時間が雨を降らす時間分を超えたとき
			if (this->rainTime < this->nowTime)
			{
				this->nowSituation = Situation::Rainfrom;
				this->nowTime = 0;
			}
			else
			{
				this->nowMove = this->move;
				this->MoveGASCheck(this->nowMove);
				this->Friction();
			}
			//画面外処理
			if (this->position.y < 0.f - this->Scale.y)
			{
				this->Kill();
			}
			break;
		case Water::Situation::Rainfrom:
			if (this->nowTime < 10)
			{
				if (this->nowTime % 2 == 0)
				{
					float rand = random::GetRand(this->position.x + 12, this->position.x + this->maxSize.x - 12.f);
					auto water = Water::Create(Vec2(rand, this->position.y + this->maxSize.x / 2));
					water->SetMaxSize(Vec2(32, 32));
					water->SetTexture(rm->GetTextureData((std::string)"waterTex"));
					water->SetWaterVolume(this->volume / 5.f);
					water->SetColor(this->color);
				}
				this->nowTime++;
			}
			else
			{
				//雨を出現したあとも少しだけ残る
				this->nowTime++;
				this->color_a.alpha -= 0.02f;
				if (this->nowTime > 40)
				{
					this->Kill();
				}
			}
			break;
		}
	case Water::State::SOLID:
		//氷処理
		if (this->HeadSolidCheck())
		{
			this->SolidMelt();
		}
		if (!this->hold)
		{
			this->Friction();	
			this->nowMove = this->move;
			this->MoveSOILDCheck(this->nowMove);
			this->SolidExtrusion();
		}
		break;
	}
}

Water::Situation Water::UpNewform()
{
	Water::Situation now = this->nowSituation;
	this->setTime++;
	this->Scale.x += 2;
	this->Scale.y += 2;
	this->position.x--;
	if (this->setTime >= this->maxSize.x / 2)
	{
		now = Water::Situation::Normal;
	}
	return now;
}

Water::Situation Water::UpDeleteform()
{
	Water::Situation now = this->nowSituation;
	++this->nowTime;
	if (this->nowTime >= 72)
	{
		now = Water::Situation::CreaDelete;
	}
	if (soundplay)
	{
		volControl.Play(&this->position, 1000.0f, 1.0f, sound);

		sound.play();
		soundplay = false;   //連続して再生されることを防ぐ
	}
	return now;
}

Water::Situation Water::UpNormal()
{
	
	Water::Situation now = this->nowSituation;
	this->Friction();
	return now;
}

void Water::Render2D()
{
	if (this->nowSituation == Situation::CreaDelete && this->currentState == State::LIQUID)
	{
		return;
	}
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 256, 256);
	if (this->currentState == State::GAS)
	{
		src.x += 256;
	}
	if (this->currentState == State::SOLID)
	{
		src.x += 512;
	}
	if (this->currentState == State::LIQUID && this->nowSituation == Situation::Deleteform)
	{
		src.y += 256;
		src.x = (float)((this->nowTime / 6) * 256);
	}
	src.OffsetSize();
	this->tex->Draw(draw, src, color_a);
	LineDraw();
}

bool Water::Finalize()
{
	return true;
}

void Water::SetState(const State& s_)
{
	this->currentState = s_;
}

Water::State Water::GetState() const
{
	return currentState;
}

void Water::SetSituation(const Situation& s_)
{
	this->nowSituation = s_;
}

Water::Situation Water::GetSituation() const
{
	return this->nowSituation;
}

float Water::waterMove()
{
	float _v = 0;
	if (this->IsBucket())
	{
		_v = this->volume;
		this->volume = 0.f;
	}
	else
	{
		return 0.0f;
	}
	this->Kill();
	return _v;
}

float Water::GetWaterVolume() const
{
	return this->volume;
}

void Water::SetTexture(Texture* texture)
{
	this->tex = texture;
}

void Water::Friction()
{
	if (this->move.x > 0)
	{
		this->move.x = std::max(this->move.x - this->finSpeed, 0.f);
	}
	else
	{
		this->move.x = std::min(this->move.x + this->finSpeed, 0.f);
	}
	if (this->currentState != State::GAS)
	{
		if (!this->FootCheck(std::string("Floor")) || !this->FootSolidCheck() || this->move.y < 0)
		{
			this->move.y = std::min(this->move.y + this->gravity, this->maxFall);
		}
		else
		{
			this->move.y = 0.0f;
		}
	}
}
bool Water::FootCheck(const std::string& objtag, const int n)
{
	GameObject foot;
	float x_ = this->Scale.x - (this->Scale.x * this->Radius.x);
	float y_ = this->Scale.y - (this->Scale.y * this->Radius.y);
	foot.CreateObject(Objform::Cube, Vec2(this->position.x + (x_ / 2.f), this->position.y + this->Scale.y + (y_ / 2.f)), Vec2(this->Scale.x - x_, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (!map)
	{
		return false;
	}
	if (map->HitCheck(foot, objtag))
	{
		return true;
	}
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = blocks->begin(); id != blocks->end(); ++id)
	{
		if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (foot.hit(*(*id)))
			{
				return true;
			}
		}
	}
	auto doors = OGge->GetTasks<Door>("Door");
	for (auto id = doors->begin(); id != doors->end(); ++id)
	{
		if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (foot.hit(*(*id)))
			{
				return true;
			}
		}
	}
	if (this->currentState == State::SOLID)
	{
		auto buckets = OGge->GetTasks<Bucket>("bucket");
		for (auto id = buckets->begin(); id != buckets->end(); ++id)
		{
			if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (foot.hit(*(*id)))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Water::FootSolidCheck()
{
	GameObject foot;
	float x_ = this->Scale.x - (this->Scale.x * this->Radius.x);
	float y_ = this->Scale.y - (this->Scale.y * this->Radius.y);
	foot.CreateObject(Objform::Cube, Vec2(this->position.x + (x_ / 2.f), this->position.y + this->Scale.y + (y_ / 2.f) + 0.1f), Vec2(this->Scale.x - x_, 0.9f), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if (this->id != (*id)->id)
		{
			if ((*id)->objectTag == "SOLID")
			{
				if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
				{
					if (foot.CubeHit(*(*id)))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Water::MoveWATERCheck(Vec2& est)
{
	auto map = OGge->GetTask<Map>("map");
	auto doors = OGge->GetTasks<Door>("Door");
	if (!map)
	{
		this->position += est;
		return;
	}
	while (est.x != 0.f)
	{
		float preX = this->position.x;
		if (est.x >= 1.f)
		{
			this->position.x += 1.f;
			est.x -= 1.f;
		}
		else if (est.x <= -1.f)
		{
			this->position.x -= 1.f;
			est.x += 1.f;
		}
		else
		{
			this->position.x += est.x;
			est.x = 0.f;
		}
		if (map->HitCheck(*this, 0))
		{
			this->position.x = preX;
			break;
		}
		for (auto id = doors->begin(); id != doors->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				//if (this->hit(*(*id)))
				if((*id)->hit(*this))
				{
					this->position.x = preX;
					break;
				}
			}
		}
	}
	while (est.y != 0.f)
	{
		float preY = this->position.y;
		if (est.y >= 1.f)
		{
			this->position.y += 1.f;
			est.y -= 1.f;
		}
		else if (est.y <= -1.f)
		{
			this->position.y -= 1.f;
			est.y += 1.f;
		}
		else
		{
			this->position.y += est.y;
			est.y = 0.f;
		}
		if (map->HitCheck(*this, 0))
		{
			this->position.y = preY;
			break;
		}
		for (auto id = doors->begin(); id != doors->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if ((*id)->hit(*this))
				{
					this->position.y = preY;
					break;
				}
			}
		}
	}
	if ((map && map->HitCheck(*this, 0) || 
		this->FootCheck((std::string)"Floor") || 
		this->FootCheck((std::string)"Soil") || 
		this->FootCheck((std::string)"Ladder") ||
		this->FootCheck("door")))
	{
		this->nowSituation = Water::Situation::Deleteform;
		this->nowTime = 0;
		this->move = { 0,0 };
	}
}

void Water::MoveGASCheck(Vec2& est)
{
	auto map = OGge->GetTask<Map>("map");
	auto doors = OGge->GetTasks<Door>("Door");
	while (est.x != 0.f)
	{
		float preX = this->position.x;
		if (est.x >= 1.f)
		{
			this->position.x += 1.f;
			est.x -= 1.f;
		}
		else if (est.x <= -1.f)
		{
			this->position.x -= 1.f;
			est.x += 1.f;
		}
		else
		{
			this->position.x += est.x;
			est.x = 0.f;
		}
		if (map->HitCheck(*this, 0))
		{
			this->position.x = preX;
			break;
		}
		for (auto id = doors->begin(); id != doors->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.x = preX;
					break;
				}
			}
		}
	}
	while (est.y != 0.f)
	{
		float preY = this->position.y;
		if (est.y >= 1.f)
		{
			this->position.y += 1.f;
			est.y -= 1.f;
		}
		else if (est.y <= -1.f)
		{
			this->position.y -= 1.f;
			est.y += 1.f;
		}
		else
		{
			this->position.y += est.y;
			est.y = 0.f;
		}
		if (map->HitCheck(*this, 0))
		{
			this->position.y = preY;
			break;
		}
		for (auto id = doors->begin(); id != doors->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.y = preY;
					break;
				}
			}
		}
	}
}

void Water::MoveSOILDCheck(Vec2& est)
{
	auto map = OGge->GetTask<Map>("map");
	auto waters = OGge->GetTasks<Water>("water");
	auto blocks = OGge->GetTasks<Block>("block");
	auto doors = OGge->GetTasks<Door>("Door");
	//テスト用追加
	auto Wswitch = OGge->GetTasks<WeightSwitch>("WeightSwitch");

	while (est.x != 0.f)
	{
		float preX = this->position.x;
		if (est.x >= 1.f)
		{
			this->position.x += 1.f;
			est.x -= 1.f;
		}
		else if (est.x <= -1.f)
		{
			this->position.x -= 1.f;
			est.x += 1.f;
		}
		else
		{
			this->position.x += est.x;
			est.x = 0.f;
		}
		if (map->HitCheck(*this, 1))
		{
			this->position.x = preX;
			break;
		}
		for (auto id = waters->begin(); id != waters->end(); ++id)
		{
			if (this->id != (*id)->id)
			{
				if ((*id)->objectTag == "SOLID")
				{
					if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
					{
						if (this->CubeHit(*(*id)))
						{
							this->position.x = preX;
							break;
						}
					}
				}
			}
		}
		for (auto id = blocks->begin(); id != blocks->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.x = preX;
					break;
				}
			}
		}
		for (auto id = doors->begin(); id != doors->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.x = preX;
					break;
				}
			}
		}
		//テスト用追加
		for (auto id = Wswitch->begin(); id != Wswitch->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.x = preX;
					break;
				}
			}
		}

	}
	while (est.y != 0.f)
	{
		float preY = this->position.y;
		if (est.y >= 1.f)
		{
			this->position.y += 1.f;
			est.y -= 1.f;
		}
		else if (est.y <= -1.f)
		{
			this->position.y -= 1.f;
			est.y += 1.f;
		}
		else
		{
			this->position.y += est.y;
			est.y = 0.f;
		}
		if (map->HitCheck(*this, 1))
		{
			this->position.y = preY;
			break;
		}
		for (auto id = waters->begin(); id != waters->end(); ++id)
		{
			if (this->id != (*id)->id)
			{
				if ((*id)->objectTag == "SOLID")
				{
					if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
					{
						if (this->CubeHit(*(*id)))
						{
							this->position.y = preY;
							break;
						}
					}
				}
			}
		}
		for (auto id = blocks->begin(); id != blocks->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.y = preY;
					break;
				}
			}
		}
		for (auto id = doors->begin(); id != doors->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.y = preY;
					break;
				}
			}
		}
		//テスト用追加
		for (auto id = Wswitch->begin(); id != Wswitch->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.y = preY;
					this->position.y += (*id)->SetSwitchUpPos();
					break;
				}
			}
		}

	}
}

bool Water::HeadCheck(const std::string& objtag, const int n)
{
	GameObject head;
	float x_ = this->Scale.x - (this->Scale.x * this->Radius.x);
	float y_ = this->Scale.y - (this->Scale.y * this->Radius.y);

	head.CreateObject(Objform::Cube, Vec2(this->position.x + (x_ / 2.f), this->position.y + (y_ / 2.f) - 1.0f), Vec2(this->Scale.x - x_, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (map->HitCheck(head, 0))
	{
		return true;
	}
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = blocks->begin(); id != blocks->end(); ++id)
	{
		if (head.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (head.hit(*(*id)))
			{
				return true;
			}
		}
	}
	return false;
}

bool Water::HeadSolidCheck()
{
	GameObject head;
	float x_ = this->Scale.x - (this->Scale.x * this->Radius.x);
	float y_ = this->Scale.y - (this->Scale.y * this->Radius.y);
	head.CreateObject(Objform::Cube, Vec2(this->position.x + (x_ / 2.f), this->position.y + (y_ / 2.f) - 3.0f), Vec2(this->Scale.x - x_, 3.0f), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if (this->id != (*id)->id)
		{
			if (head.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if ((*id)->objectTag == "SOLID")
				{
					if (head.CubeHit(*(*id)))
					{
						return true;
					}
				}
			}
		}
	}
	auto doors = OGge->GetTasks<Door>("Door");
	for (auto id = doors->begin(); id != doors->end(); ++id)
	{
		if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (this->CubeHit(*(*id)))
			{
				return true;
			}
		}
	}
	if (!this->hold)
	{
		auto player = OGge->GetTasks<Player>("Player");
		for (auto id = player->begin(); id != player->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (head.CubeHit(*(*id)))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Water::SetColor(const Paint::PaintColor& color)
{
	//色の変化は液体の時に限定する
	if (this->currentState == State::LIQUID)
	{
		if (this->color == Paint::PaintColor::Purple)
		{
			//紫なら色の変化を行わない
		}
		else if (this->color == Paint::PaintColor::Blue && color == Paint::PaintColor::Red)
		{
			//青と赤で紫へ
			this->color = Paint::PaintColor::Purple;
		}
		else if (this->color == Paint::PaintColor::Red && color == Paint::PaintColor::Blue)
		{
			//赤と青で紫へ
			this->color = Paint::PaintColor::Purple;
		}
		else
		{
			//それ以外はそのまま変化させる
			this->color = color;
		}
	}
	//色に合わせて使用する画像を変える
	switch (this->color)
	{
	case Paint::PaintColor::Red:
		this->SetTexture(rm->GetTextureData((std::string)"waterRed"));
		break;
	case Paint::PaintColor::Blue:
		this->SetTexture(rm->GetTextureData((std::string)"waterBlue"));
		break;
	case Paint::PaintColor::Purple:
		this->SetTexture(rm->GetTextureData((std::string)"waterPurple"));
		break;
	default:
		this->SetTexture(rm->GetTextureData((std::string)"waterTex"));
		break;
	}
	return true;
}

Paint::PaintColor Water::GetColor() const
{
	return this->color;
}

void Water::MovePos(const Vec2& est)
{
	this->move = est;
}

Vec2 Water::GetMove() const
{
	return this->move;
}

bool Water::IsBucket()
{
	return this->GetSituation() == Water::Situation::Normal && this->GetState() == Water::State::LIQUID && this->invi <= 0;
}

void Water::SetMaxSize(const Vec2& max)
{
	this->maxSize = max;
}

void Water::SetWaterVolume(float value)
{
	this->volume = value;
}

Vec2 Water::MoveSolid(const Vec2& est)
{
	this->move.x = est.x;
	this->nowMove = move;
	this->MoveSOILDCheck(this->nowMove);
	return this->nowMove;
}

void Water::HoldCheck(bool flag)
{
	if (flag)
	{
		if (this->GetState() == State::SOLID)
		{
			this->hold = true;
			return;
		}
	}
	this->hold = false;
}

bool Water::GetHold() const
{
	return this->hold;
}

void Water::ResetMove()
{
	this->move = { 0,0 };
}

void Water::CheckState()
{
	if (this->preState != this->currentState)
	{
		this->preState = this->currentState;
		switch (this->currentState)
		{
		case State::GAS:
			this->Scale = this->maxSize;
			this->objectTag = "GAS";
			this->Radius = { 0.5f,0.8f };
			this->nowSituation = Situation::Normal;
			this->finSpeed = 1.0f;
			break;
		case State::LIQUID:
			this->Radius = { 0.5f,0.9f };
			this->objectTag = "LIQUID";
			this->finSpeed = 1.0f;
			break;
		case State::SOLID:
			this->Scale = this->maxSize;
			auto waters = OGge->GetTasks<Water>("water");
			for (auto id = waters->begin(); id != waters->end(); ++id)
			{
				//自分以外のIDであり
				if (this->id != (*id)->id)
				{
					//状態が氷であり
					if ((*id)->GetState() == State::SOLID)
					{
						//当たり判定を行う空間にいる時
						if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
						{
							//当たり判定を行う
							if (this->CubeHit(*(*id)))
							{
								//相手を水に移行させる
								(*id)->SetSituation(Situation::Normal);
								(*id)->SetState(State::LIQUID);
							}
						}
					}
				}
			}
			this->objectTag = "SOLID";
			this->Radius = { 0.7f,0.7f };
			this->nowSituation = Situation::Normal;
			this->finSpeed = 0.05f;
			break;
		}
	}
}

void Water::MovePos_x(float est)
{
	this->move.x = est;
}

void Water::SolidMelt()
{
	if (this->currentState == State::SOLID)
	{
		if (this->hold)
		{
			auto player = OGge->GetTask<Player>("Player");
			if (player)
			{
				//player->ReleaseHold();
				player->ReleaseSolid();
				player->SetState(Player::State::NORMAL);
				player->SetMotion(Player::Motion::Normal);
			}
		}
		this->SetState(State::LIQUID);
		this->SetSituation(Situation::Normal);
		//氷が溶けた時のエフェクト
		auto effect = Effect::Create(
			Vec2(this->position.x + (this->Scale.x / 2.f) - (128.f / 2.f), this->position.y + this->Scale.y - (128.f / 1.5f)),
			Vec2(128, 128),
			Vec2(768, 768),
			1,
			150);
		effect->SetTexture(rm->GetTextureData((std::string)"steam"));
		effect->SetMode(Effect::Mode::Decrease);
		//effect->SetMaxSize(Vec2(80, 80));
		effect->Set(effect->position, Vec2(effect->position.x, effect->position.y - 200), 30);
	}
}
void Water::SetScale(const Vec2& s)
{
	this->Scale = s;
}
unsigned int Water::GetID() const
{
	return this->id;
}
bool Water::SolidExtrusion()
{
	auto waters = OGge->GetTasks<Water>("water");
	float x_ = this->Scale.x - (this->Scale.x * this->Radius.x);
	float y_ = this->Scale.y - (this->Scale.y * this->Radius.y);
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		//自分以外でありかつ相手が氷であるとき
		if (this->id != (*id)->id && (*id)->objectTag == "SOLID")
		{
			//自分の周辺に相手が存在する場合
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				//移動値がプラスなら
				if(this->move.x > 0)
				{
					//左方向の当たり判定が存在しないなら生成
					if (!this->right)
					{
						this->right = new GameObject();
						right->CreateObject(Cube,
							Vec2(this->position.x + (x_ / 2.f) + (this->Scale.x * this->Radius.x), this->position.y + (y_ / 2.f)),
							Vec2(1.0f, this->Scale.y - y_));
					}
					//当たっているか確認
					if (right->CubeHit(*(*id)))
					{
						//相手を移動させる
						((*id))->MoveSolid(this->move);
						delete this->right;
						this->right = nullptr;
						this->move.x = 0.f;
						return true;
					}
				}
				//移動値がマイナスなら
				if (this->move.x < 0)
				{
					//右方向の当たり判定が存在しないなら生成
					if (!this->left)
					{
						this->left = new GameObject();
						left->CreateObject(Cube,
							Vec2(this->position.x + (x_ / 2.f) - 1.0f, this->position.y + (y_ / 2.f)),
							Vec2(1.0f, this->Scale.y - y_));
					}
					//当たっているか確認
					if (left->CubeHit(*(*id)))
					{
						//相手を移動させる
						((*id))->MoveSolid(this->move);
						delete this->left;
						this->left = nullptr;
						this->move.x = 0.f;
						return true;
					}
				}
			}
		}
	}
	if (this->left)
	{
		delete this->left;
		this->left = nullptr;
	}
	if (this->right)
	{
		delete this->right;
		this->right = nullptr;
	}
	return false;
}
Water::SP Water::Create(const Vec2& pos)
{
	auto to = Water::SP(new Water(pos));
	if (to)
	{
		to->me = to;
		OGge->SetTaskObject(to);
		if (!to->Initialize())
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
void Water::SetIceCnt(const unsigned int& n)
{
	this->iceCnt = n;
}
unsigned int Water::GetIceCnt() const
{
	return this->iceCnt;
}
void Water::SetFireCnt(const unsigned int& n)
{
	this->fireCnt = n;
}
unsigned int Water::GetFireCnt() const
{
	return this->fireCnt;
}