#include "ResultPlayer.h"
bool ResultPlayer::Initialize(Vec2& pos,Vec2& speed)
{
	this->taskName = "ResultPlayer";
	this->Init(taskName);
	std::string filePath = "walk.png";
	image.Create(filePath);
	this->CreateObject(Cube, pos, Vec2(64, 64), 0);
	this->moveVec = speed;
	this->SetDrawOrder(1.0f);
	std::cout << "リザルト時プレイヤ　初期化" << std::endl;
	return true;
}
bool ResultPlayer::Finalize()
{
	image.Finalize();
	return true;
}
void ResultPlayer::UpDate()
{
	Move();
}
void ResultPlayer::Move()
{
	Vec2 windowsize = OGge->camera->GetSize();
	if(position.x <= windowsize.x)
	{
		position.x += moveVec.x;
	}
	else
	{
		Kill();
	}
}
void ResultPlayer::Render2D()
{
	Box2D draw(position, Scale);
	draw.OffsetSize();
	Box2D src = this->Src;
	src.OffsetSize();

	int temp = src.w;
	src.w = src.x;
	src.x = temp;
	image.Draw(draw, src);
}
ResultPlayer::ResultPlayer()
{
	std::cout << "リザルト時プレイヤ　生成" << std::endl;
}
ResultPlayer::~ResultPlayer()
{
	std::cout << "リザルト時プレイヤ　解放" << std::endl;
}
ResultPlayer::SP ResultPlayer::Create(Vec2 pos,Vec2 speed,bool flag)
{
	ResultPlayer::SP to = ResultPlayer::SP(new ResultPlayer());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,speed))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}