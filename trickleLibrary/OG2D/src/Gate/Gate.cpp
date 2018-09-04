#include "Gate.h"


Gate::Gate(const Vec2& pos)
{
	//オブジェクトを生成
	this->CreateObject(Cube, pos, Vec2(230, 260), 0.0f);     //460,512,70    元データx192,y384    比率変更x345,y384
															 //ドア位置を登録
	this->door_x = this->position.x + 35;
	this->door_w = this->position.x + this->Scale.x - 35;
	//タグを指定、スーパークラスに登録
	this->objectTag = "gate";
	__super::Init(this->objectTag);
	__super::SetDrawOrder(0.7f);
	//画像データ初期化
	this->image = nullptr;
	//サウンドのファイル名初期化
	this->soundopenname = "doorOpen.wav";
	this->soundclosename = "doorClose.wav";
	//サウンド生成
	soundOpen.create(soundopenname, false);
	soundOpen.volume(1.0f);
	soundClose.create(soundclosename, false);
	soundClose.volume(1.0f);
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
		soundOpen.play();
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
		//扉が閉じるタイミングと音が合わない
		//soundClose.play();
		soundOpen.play();
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