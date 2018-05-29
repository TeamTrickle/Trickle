#include "water.h"
#include "Map\Map.h"
#include "Block\block.h"


Water::Water(Vec2 pos)
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
	//デバッグ用位置調整
	//this->position = { 28 * 64 + 32, 12 * 64 };//ゴール位置
	//this->position = { 19 * 64 + 32,13 * 64 };//加熱器上
	//初期ステータスの設定
	this->nowSituation = Water::Situation::Newfrom;
	this->currentState = Water::State::LIQUID;
	this->preState = Water::State::LIQUID;
	//テスト
	/*this->nowSituation = Water::Situation::Normal;
	this->currentState = Water::State::SOLID;*/
	//初期保持水量
	this->volume = 0.5;
	this->invi = 0;
	//移動値の初期化
	this->move = { 0,0 };
	//経過時間初期化
	this->nowTime = 0;
	//現在カラーを設定
	this->color = { 0,0,0,0 };
	//IDを設定
	auto waters = OGge->GetTasks<Water>("water");
	int i = 0;
	auto id = waters->begin();
	while (id != waters->end())
	{
		++i;
		++id;
	}
	this->id = i;
	//サウンドのファイル名設定
	soundname = "water-drop3.wav";
	this->hold = false;
	this->Radius = { 0.5f,0.9f };
}

Water::~Water() 
{
	
}


bool Water::Initialize() 
{
	__super::Init((std::string)"water");
	soundplay = true;
	sound.create(soundname, false);
	sound.volume(1.0f);
	OGge->soundManager->SetSound(&sound);

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
			this->MoveWATERCheck(move);
			break;
		case Water::Situation::Deleteform:
			this->nowSituation = Water::UpDeleteform();
			if (soundplay)
			{
				sound.play();
				soundplay = false;   //連続して再生されることを防ぐ
			}
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
			if (this->RAIN_TIME < this->nowTime)
			{
				this->nowSituation = Situation::Rainfrom;
				this->position.x += this->maxSize.x / 2;
			}
			else
			{
				this->MoveGASCheck(move);
				this->Friction();
			}
			break;
		case Water::Situation::Rainfrom:
			this->nowSituation = Situation::Newfrom;
			this->currentState = State::LIQUID;
			this->Scale = this->minSize;
			this->setTime = 0;
			break;
		}
		break;
	case Water::State::SOLID:
		//氷処理
		if (!this->hold)
		{
			this->Friction();
			this->MoveSOILDCheck(move);
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
	return now;
}

Water::Situation Water::UpNormal()
{
	Water::Situation now = this->nowSituation;
	if (this->FootCheck((std::string)"Floor") || this->FootCheck((std::string)"Soil"))
	{
		now = Water::Situation::Deleteform;
		this->nowTime = 0;
	}
	else
	{
		this->Friction();
	}
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
		src.x = (this->nowTime / 6) * 256;
	}
	src.OffsetSize();
	this->tex->Draw(draw, src, Color{ 1.f - color.red,1.f - this->color.green,1.f - this->color.blue,1.f - this->color.alpha });
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
		this->move.x = std::max(this->move.x - this->FIN_SPEED, 0.f);
	}
	else
	{
		this->move.x = std::min(this->move.x + this->FIN_SPEED, 0.f);
	}
	if (this->currentState != State::GAS)
	{
		if (!this->FootCheck(std::string("Floor")) || !this->FootCheck(std::string("SOLID")) || this->move.y < 0)
		{
			this->move.y = std::min(this->move.y + this->GRAVITY, this->MAX_FALL);
		}
		else
		{
			this->move.y = 0.0f;
		}
	}
}
bool Water::FootCheck(std::string& objtag,int n)
{
	GameObject foot;
	float x_ = this->Scale.x - (this->Scale.x * this->Radius.x);
	float y_ = this->Scale.y - (this->Scale.y * this->Radius.y);
	foot.CreateObject(Objform::Cube, Vec2(this->position.x + (x_ / 2.f), this->position.y + this->Scale.y + (y_ / 2.f) + 0.1f), Vec2(this->Scale.x - x_, 0.9f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (!map)
	{
		return false;
	}
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (foot.hit(map->hitBase[y][x]))
			{
				
				if (map->hitBase[y][x].objectTag == objtag)
				{
					return true;
				}
			}
		}
	}
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = blocks->begin(); id != blocks->end(); ++id)
	{
		if (foot.hit(*(*id)))
		{
			return true;
		}
	}
	return false;
}

void Water::MoveWATERCheck(Vec2 est)
{
	auto map = OGge->GetTask<Map>("map");
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
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag == "Floor" || map->hitBase[y][x].objectTag == "Soil")
				{
					if (this->hit(map->hitBase[y][x]))
					{
						this->position.x = preX;
						break;
					}
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
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag == "Floor" || map->hitBase[y][x].objectTag == "Soil")
				{
					if (this->hit(map->hitBase[y][x]))
					{
						this->position.y = preY;
						break;
					}
				}
			}
		}
	}
}

void Water::MoveGASCheck(Vec2 est)
{
	auto map = OGge->GetTask<Map>("map");
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
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag == "Floor")
				{
					if (this->hit(map->hitBase[y][x]))
					{
						this->position.x = preX;
						break;
					}
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
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag == "Floor")
				{
					if (this->hit(map->hitBase[y][x]))
					{
						this->position.y = preY;
						break;
					}
				}
			}
		}
	}
}

void Water::MoveSOILDCheck(Vec2 est)
{
	auto map = OGge->GetTask<Map>("map");
	auto waters = OGge->GetTasks<Water>("water");
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
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag == "Floor" || 
					map->hitBase[y][x].objectTag == "Soil" || 
					map->hitBase[y][x].objectTag == "Net")
				{
					if (this->hit(map->hitBase[y][x]))
					{
						this->position.x = preX;
						break;
					}
				}
			}
		}
		for (auto id = waters->begin(); id != waters->end(); ++id)
		{
			if (this->id != (*id)->id)
			{
				if ((*id)->objectTag == "SOLID")
				{
					if (this->hit(*(*id)))
					{
						this->position.x = preX;
						break;
					}
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
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag == "Floor" ||
					map->hitBase[y][x].objectTag == "Soil" ||
					map->hitBase[y][x].objectTag == "Net")
				{
					if (this->hit(map->hitBase[y][x]))
					{
						this->position.y = preY;
						break;
					}
				}
			}
		}
		for (auto id = waters->begin(); id != waters->end(); ++id)
		{
			if (this->id != (*id)->id)
			{
				if ((*id)->objectTag == "SOLID")
				{
					if (this->hit(*(*id)))
					{
						this->position.y = preY;
						break;
					}
				}
			}
		}
	}
}

bool Water::HeadCheck(std::string& objtag,int n)
{
	GameObject head;
	float x_ = this->Scale.x - (this->Scale.x * this->Radius.x);
	float y_ = this->Scale.y - (this->Scale.y * this->Radius.y);

	head.CreateObject(Objform::Cube, Vec2(this->position.x + (x_ / 2.f), this->position.y + (y_ / 2.f) - 1.0f), Vec2(this->Scale.x - x_, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (head.hit(map->hitBase[y][x]))
			{
				if (map->hitBase[y][x].objectTag == objtag || 
					map->_arr[y][x] == 24)
				{
					return true;
				}
			}
		}
	}
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = blocks->begin(); id != blocks->end(); ++id)
	{
		if (head.hit(*(*id)))
		{
			return true;
		}
	}
	return false;
}

bool Water::SetColor(Color& color)
{
	this->color = color;
	return true;
}

Color Water::GetColor() const
{
	return this->color;
}

void Water::MovePos(Vec2& est)
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

void Water::SetMaxSize(Vec2& max)
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
	//this->MoveSOILDCheck(this->move);
	return this->move;
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
			break;
		case State::LIQUID:
			this->Radius = { 0.5f,0.9f };
			this->objectTag = "LIQUID";
			break;
		case State::SOLID:
			this->Scale = this->maxSize;
			this->objectTag = "SOLID";
			this->Radius = { 1.0f,1.0f };
			this->nowSituation = Situation::Normal;
			break;
		}
	}
}

void Water::MovePos_x(float est)
{
	this->move.x = est;
}

Water::SP Water::Create(Vec2& pos, bool flag_)
{
	auto to = Water::SP(new Water(pos));
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize())
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}