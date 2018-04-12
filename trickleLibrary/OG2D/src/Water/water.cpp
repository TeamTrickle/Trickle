#include "water.h"



Water::Water(Vec2 pos) {
	//タグ設定
	this->objectTag = "Water";
	//衝突判定
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Floor") {
			this->isCollided = true;
		}
		if (o_.objectTag == "baketu")
		{
			if (this->GetState() == Water::State::LIQUID && this->GetSituation() == Water::Situation::Normal) {
				this->SetSituation(Water::Situation::CreaDelete);
			}
		}
		if (o_.objectTag == "Soil")
		{
			this->isCollided = true;
		}
	};
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
	//テクスチャの読み込み
	tex.TextureCreate("watertest.png");
	//衝突判定の初期化
	this->isCollided = false;
	//初期ステータスの設定
	this->nowSituation = Water::Situation::Newfrom;
	this->currentState = Water::State::LIQUID;
	//初期保持水量
	this->volume = 0.5;
	this->invi = 0;
}

Water::~Water() {
	//テクスチャの解放
	tex.Finalize();
}


bool Water::Initialize() {
	this->objectTag = "Water";
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Floor") {
			this->isCollided = true;
		}
	};
	CreateObject(Objform::Cube, Vec2(100, 100), Vec2(64, 64), 0.f);
	this->isCollided = false;
	return true;
}

void Water::Update() {
	if (this->invi > 0)
	{
		this->invi--;
	}
	switch (this->currentState) {
	case Water::State::LIQUID:
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
		break;
	case Water::State::GAS:
		//水蒸気処理
		this->Scale = { this->maxSize.x,this->maxSize.y };
		if (!this->isCollided)
		{
			this->position.y -= 2.f;
		}
		break;
	case Water::State::SOLID:
		//氷処理
		this->Scale = this->maxSize;
		if (!isCollided)
		{
			this->position.y += 5.0f;

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
	if (!this->isCollided)
	{
		position.y += 5.0f;
	}
	else
	{
		now = Water::Situation::Deleteform;
	}
	return now;
}

void Water::Render() {
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src = drawRange[currentState];
	src.OffsetSize();
	tex.Draw(draw, src);
}

void Water::Finalize() {
	tex.Finalize();
	//delete this;
}

void Water::SetState(const State& s_) {
	this->currentState = s_;
}

Water::State Water::GetState() const {
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