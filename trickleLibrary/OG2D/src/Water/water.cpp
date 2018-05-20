#include "water.h"
#include "Map\Map.h"


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
	//this->position = { 28 * 64 + 32, 12 * 64 };
	//テクスチャの読み込み
	//tex.Create("watertest.png");
	//初期ステータスの設定
	this->nowSituation = Water::Situation::Newfrom;
	this->currentState = Water::State::LIQUID;
	//初期保持水量
	this->volume = 0.5;
	this->invi = 0;
	//移動値の初期化
	this->move = { 0,0 };
	//経過時間初期化
	this->nowTime = 0;
	//現在カラーを設定
	this->color = { 0,0,0,0 };
}

Water::~Water() 
{
	
}


bool Water::Initialize() 
{
	__super::Init((std::string)"water");
	return true;
}

void Water::UpDate()
{
	if (this->invi > 0)
	{
		this->invi--;
	}
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
			break;
		case Water::Situation::CreaDelete:
			this->Kill();
			break;
		}
		break;
	case Water::State::GAS:
		switch (this->nowSituation)
		{
		case Water::Situation::Normal:
			this->objectTag = "GAS";
			//水蒸気処理
			this->Scale = this->maxSize;
			if (!this->HeadCheck((std::string)"Floor"))
			{
				this->move.y -= 3.0f;
				this->nowTime = 0;
			}
			else
			{
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
			}
			break;
		case Water::Situation::Rainfrom:
			this->nowSituation = Situation::Newfrom;
			this->currentState = State::LIQUID;
			this->Scale = this->minSize;
			this->setTime = 0;
			break;
		case Water::Situation::Newfrom:
			this->nowSituation = Water::Situation::Normal;
			break;
		case Water::Situation::Deleteform:
			this->nowSituation = Water::Situation::Normal;
			break;
		}
		break;
	case Water::State::SOLID:
		this->objectTag = "SOLID";
		//氷処理
		this->Scale = this->maxSize;
		this->Friction();
		this->MoveSOILDCheck(move);
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
	/*this->setTime++;
	this->Scale.x -= 2;
	this->Scale.y -= 2;
	this->position.y += 2;
	this->position.x++;*/
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
		this->move.x = std::min(this->move.x + this->FIN_SPEED, 0.f);
	}
	else
	{
		this->move.x = std::max(this->move.x - this->FIN_SPEED, 0.f);
	}
	if (!this->FootCheck(std::string("Floor")) || !this->FootCheck(std::string("SOLID")) || this->move.y < 0)
	{
		this->move.y = std::min(this->move.y + this->GRAVITY, this->MAX_FALL);
	}
	else
	{
		this->move.y = 0.0f;
	}
}
bool Water::FootCheck(std::string& objtag,int n)
{
	GameObject foot;
	foot.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y + this->Scale.y + 0.1f), Vec2(this->Scale.x, 0.9f), 0.0f);
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
				if (n == 0)
				{
					if (map->hitBase[y][x].objectTag == objtag)
					{
						return true;
					}
				}
				else
				{
					if (map->hitBase[y][x].objectTag != objtag)
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

void Water::MoveGASCheck(Vec2& est)
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

void Water::MoveSOILDCheck(Vec2& est)
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
				if (map->hitBase[y][x].objectTag == "Floor" || 
					map->hitBase[y][x].objectTag == "Soil" || 
					map->hitBase[y][x].objectTag == "Net" || 
					map->hitBase[y][x].objectTag == "SOLID")
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
				if (map->hitBase[y][x].objectTag == "Floor" ||
					map->hitBase[y][x].objectTag == "Soil" ||
					map->hitBase[y][x].objectTag == "Net" ||
					map->hitBase[y][x].objectTag == "SOLID")
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

bool Water::HeadCheck(std::string& objtag,int n)
{
	GameObject head;
	head.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y - 1.0f), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (head.hit(map->hitBase[y][x]))
			{
				if (n == 0)
				{
					if (map->hitBase[y][x].objectTag == objtag)
					{
						return true;
					}
				}
				else
				{
					if (map->hitBase[y][x].objectTag != objtag)
					{
						return true;
					}
				}
			}
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
	this->move += est;
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