#include "water.h"



Water::Water(Vec2 pos)
{
	//タグ設定
	this->objectTag = "Water";
	//描画元画像座標
	this->drawRange[Water::State::LIQUID] = Box2D(0, 0, 128, 128);
	this->drawRange[Water::State::GAS] = Box2D(128, 0, 128, 128);
	this->drawRange[Water::State::SOLID] = Box2D(256, 0, 128, 128);
	//描画最大最小サイズ
	this->minSize = { 0,0 };
	this->maxSize = { 64,64 };
	//経過時間初期化
	this->setTime = 0;
	//オブジェクトの生成
	CreateObject(Objform::Cube, pos, this->minSize, 0.f);
	//デバッグ用位置調整
	//this->position = { 1186,800 };
	//テクスチャの読み込み
	//tex.TextureCreate("watertest.png");
	//衝突判定の初期化
	this->isCollided = false;
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
}

Water::~Water() 
{
	
}


bool Water::Initialize() 
{
	this->objectTag = "Water";
	CreateObject(Objform::Cube, Vec2(100, 100), Vec2(64, 64), 0.f);
	this->isCollided = false;
	return true;
}

void Water::Update()
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
			break;
		case Water::Situation::Deleteform:
			this->nowSituation = Water::UpDeleteform();
			break;
		case Water::Situation::CreaDelete:
			break;
		}
		this->MoveWATERCheck(move);
		break;
	case Water::State::GAS:
		switch (this->nowSituation)
		{
		case Water::Situation::Normal:
			this->objectTag = "GAS";
			//水蒸気処理
			this->Scale = { this->maxSize.x,this->maxSize.y };
			if (!this->HeadCheck((std::string)"Floor"))
			{
				this->move.y -= 3.0f;
				this->nowTime = 0;
			}
			else
			{
				this->nowTime++;
			}
			//静止時間が雨を降らす時間分を超えたとき
			if (this->RAIN_TIME < this->nowTime)
			{
				this->nowSituation = Situation::Rainfrom;
				this->position.x += this->maxSize.x / 2;
			}
			this->MoveGASCheck(move);
			break;
		case Water::Situation::Rainfrom:
			this->nowSituation = Situation::Newfrom;
			this->currentState = State::LIQUID;
			this->Scale = this->minSize;
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
	this->setTime++;
	this->Scale.x -= 2;
	this->Scale.y -= 2;
	this->position.y += 2;
	this->position.x++;
	if (this->setTime >= this->maxSize.x)
	{
		now = Water::Situation::CreaDelete;
	}
	return now;
}

Water::Situation Water::UpNormal()
{
	Water::Situation now = this->nowSituation;
	if (this->FootCheck((std::string)"Floor"))
	{
		now = Water::Situation::Deleteform;
	}
	else
	{
		this->Friction();
	}
	return now;
}

void Water::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src = drawRange[currentState];
	src.OffsetSize();
	this->tex->Draw(draw, src);
}

void Water::Finalize()
{
	this->AllDelete();
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
	if (Water::Situation::Normal == this->nowSituation && Water::State::LIQUID == this->currentState)
	{
		_v = this->volume;
		this->volume = 0.f;
	}	
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

void Water::SetMapObject(Object* mapobj)
{
	this->mapObj.push_back(mapobj);
}
void Water::AddObject(Object* obj_)
{
	this->objects.push_back(obj_);
}

bool Water::DeleteObject(Object* obj_)
{
	for (auto id = this->objects.begin(); id != this->objects.end(); ++id)
	{
		if ((*id) == obj_)
		{
			this->objects.erase(id);
			return true;
		}
	}
	return false;
}

void Water::AllDelete()
{
	this->objects.clear();
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
	Object foot;
	foot.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y + this->Scale.y + 0.1f), Vec2(this->Scale.x, 0.9f), 0.0f);
	for (int j = 0; j < this->objects.size(); ++j)
	{
		if (foot.hit(*this->objects[j]))
		{
			if (n == 0) {
				if (this->objects[j]->objectTag == objtag)
				{
					return true;
				}
			}
			else
			{
				if (this->objects[j]->objectTag != objtag)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Water::MoveWATERCheck(Vec2& est)
{
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
		for (int i = 0; i < this->objects.size(); ++i)
		{
			if (this->hit(*this->objects[i]))
			{
				if (this->objects[i]->objectTag == "Floor" || this->objects[i]->objectTag == "Soil") {
					//std::cout << "hit" << std::endl;
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
		for (int i = 0; i < this->objects.size(); ++i)
		{
			if (this->hit(*this->objects[i]))
			{
				if (this->objects[i]->objectTag == "Floor" || this->objects[i]->objectTag == "Soil") {
					//std::cout << "hit" << std::endl;
					this->position.y = preY;
					break;
				}
			}
		}
	}
}

void Water::MoveGASCheck(Vec2& est)
{
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
		for (int i = 0; i < this->objects.size(); ++i)
		{
			if (this->hit(*this->objects[i]))
			{
				if (this->objects[i]->objectTag == "Floor") {
					//std::cout << "hit" << std::endl;
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
		for (int i = 0; i < this->objects.size(); ++i)
		{
			if (this->hit(*this->objects[i]))
			{
				if (this->objects[i]->objectTag == "Floor") {
					//std::cout << "hit" << std::endl;
					this->position.y = preY;
					break;
				}
			}
		}
	}
}

void Water::MoveSOILDCheck(Vec2& est)
{
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
		for (int i = 0; i < this->objects.size(); ++i)
		{
			if (this->hit(*this->objects[i]))
			{
				if (this->objects[i]->objectTag == "Floor" || 
					this->objects[i]->objectTag == "Net" || 
					this->objects[i]->objectTag == "SOLID" || 
					this->objects[i]->objectTag == "Soil") 
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
		for (int i = 0; i < this->objects.size(); ++i)
		{
			if (this->hit(*this->objects[i]))
			{
				if (this->objects[i]->objectTag == "Floor" || 
					this->objects[i]->objectTag == "Net" || 
					this->objects[i]->objectTag == "SOLID" ||
					this->objects[i]->objectTag == "Soil")
				{
					this->position.y = preY;
					break;
				}
			}
		}
	}
}

bool Water::HeadCheck(std::string& objtag,int n)
{
	Object head;
	head.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y - 1.0f), Vec2(this->Scale.x, 1.0f), 0.0f);
	for (int i = 0; i < this->objects.size(); ++i)
	{
		if (head.hit(*this->objects[i]))
		{
			if (n == 0) {
				if (this->objects[i]->objectTag == objtag)
				{
					return true;
				}
			}
			else
			{
				if (this->objects[i]->objectTag != objtag)
				{
					return true;
				}
			}
		}
	}
	return false;
}