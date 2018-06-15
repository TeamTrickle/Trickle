#include "Gate.h"


Gate::Gate(const Vec2& pos)
{
	//オブジェクトを生成
	this->CreateObject(Cube, pos, Vec2(192, 384), 0.0f);
	//ドア位置を登録
	this->door_x = this->position.x + 38;
	this->door_w = this->position.x + this->Scale.x - 38;
	//タグを指定、スーパークラスに登録
	this->objectTag = "gate";
	__super::Init(this->objectTag);
	//画像データ初期化
	this->image = nullptr;
	//初期扉状態を登録
	this->isOpen = false;
	this->preIsOpen = false;
	//アニメーション用カウント初期化
	this->AnimCnt = 30;
	this->Sense = 10;
	//他のゲートの数に応じてIDを振りあてる
	auto gates = OGge->GetTasks<Gate>("gate");
	auto id = gates->begin();
	unsigned __int8 i = 0;
	while (id != gates->end())
	{
		++i;
		++id;
	}
	this->ID = i;
}

Gate::~Gate()
{
	this->image = nullptr;
}

void Gate::UpDate()
{
	if (this->isOpen != this->preIsOpen)
	{
		this->AnimCnt++;
		if (this->AnimCnt > 30)
		{
			this->preIsOpen = this->isOpen;
		}
	}
}

void Gate::Render2D()
{
	if (this->image)
	{
		this->draw = { this->position, this->Scale };
		this->draw.OffsetSize();
		if (this->isOpen)
		{
			this->src = { 460 * (this->AnimCnt / this->Sense),0,460,512 };
			this->src.OffsetSize();
		}
		else
		{
			this->src = { 460 * (3 - (this->AnimCnt / this->Sense)),0,460,512 };
			this->src.OffsetSize();
		}
		this->image->Draw(this->draw, this->src);
	}
}

void Gate::SetTexture(Texture* tex)
{
	this->image = tex;
}

unsigned __int8 Gate::GetID() const
{
	return this->ID;
}

bool Gate::ToOpen()
{
	if (!this->isOpen)
	{
		this->isOpen = true;
		this->AnimCnt = 0;
		return true;
	}
	return false;
}

bool Gate::ToClose()
{

	if (this->isOpen)
	{
		this->isOpen = false;
		this->AnimCnt = 0;
		return true;
	}
	return false;
}

float Gate::Get_Door_x() const
{
	return this->door_x;
}

float Gate::Get_Door_w() const
{
	return this->door_w;
}

Gate::SP Gate::Create(const Vec2& pos, bool flag)
{
	Gate::SP to = Gate::SP(new Gate(pos));
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		return to;
	}
	return nullptr;
}
Gate::SP Gate::Create(const float posx, const float posy, bool flag)
{
	Gate::SP to = Gate::SP(new Gate(Vec2(posx, posy)));
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		return to;
	}
	return nullptr;
}