#include "Door.h"

Door::Door(const Vec2& pos, const Vec2& size, const bool isOpen)
{
	this->objectTag = "Door";
	__super::Init(this->objectTag);
	__super::SetDrawOrder(0.5f);
	auto doors = OGge->GetTasks<Door>(this->objectTag);
	//¶¬‚³‚ê‚½‚à‚Ì‚ªI—¹ŽžˆÈŠO‰ð•ú‚³‚ê‚é‚±‚Æ‚ª‚ ‚é‚È‚ç‚±‚Á‚¿
	//for (auto id = doors->begin(); id != doors->end(); ++id)
	//{
	//}
	//‚È‚¯‚ê‚ÎŠÈˆÕŒ^
	this->id = (unsigned __int8)doors->size();
	this->isOpen = this->preIsOpen = isOpen;
	this->image = nullptr;
	this->originPos = pos;
	this->CreateObject(Cube, pos, size);
	if (this->isOpen)
	{
		this->timeCnt = 0.01f;
	}
	else
	{
		this->timeCnt = 1.f;
	}
	this->position.y = this->originPos.y - (this->Scale.y * (1.f - this->timeCnt));
	this->isMove = false;
}
Door::~Door()
{
	
}
void Door::UpDate()
{
	if (this->isOpen != this->preIsOpen)
	{
		this->isMove = true;
		if (this->isOpen)
		{
			this->timeCnt -= 0.01f;
			if (this->timeCnt <= 0.01f)
			{
				this->timeCnt = 0.01f;
				this->preIsOpen = this->isOpen;
				this->isMove = false;
			}
		}
		else
		{
			this->timeCnt += 0.01f;
			if (this->timeCnt >= 1.0f)
			{
				this->timeCnt = 1.0f;
				this->preIsOpen = this->isOpen;
				this->isMove = false;
			}
		}
		this->position.y = this->originPos.y - (this->Scale.y * (1.f - this->timeCnt));
	}
}
void Door::Render2D()
{
	if (this->image)
	{
		//this->draw = { this->position,Vec2(this->Scale.x,this->Scale.y * this->timeCnt) };
		this->draw = { this->position.x,this->position.y,this->Scale.x,this->Scale.y };
		draw.OffsetSize();
		this->src = { 0.f,0.f,this->image->GetTextureSize().x,this->image->GetTextureSize().y };
		src.OffsetSize();
		this->image->Draw(this->draw, this->src);
		this->LineDraw();
	}
}
bool Door::ToOpen()
{
	if (!this->isOpen)
	{
		this->isOpen = true;
	}
	return false;
}
bool Door::ToClose()
{
	if (this->isOpen)
	{
		this->isOpen = false;
	}
	return false;
}
bool Door::IsOpen() const
{
	return this->isOpen;
}
void Door::SetTexture(Texture* tex)
{
	this->image = tex;
}
unsigned __int8 Door::GetID() const
{
	return this->id;
}
bool Door::IsMove() const
{
	return this->isMove;
}
Door::SP Door::Create(const Vec2& pos,const Vec2& size,const bool isOpen)
{
	Door::SP to = Door::SP(new Door(pos, size, isOpen));
	if (to)
	{

		to->me = to;
		OGge->SetTaskObject(to);
		return to;
	}
	return nullptr;
}