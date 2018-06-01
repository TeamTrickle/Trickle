#include "MissionUI.h"
bool MissionUI::Initialize(Vec2& pos)
{
	this->taskName = "MissionUI";
	this->Init(taskName);
	std::cout << "ミッションUI　初期化" << std::endl;

	//Easing設定
	easingX.Init();
	easingX.ResetTime();

	CreateObject(Cube, pos, Vec2(512, 64), 0);
	//easing用に値を保存しておく
	this->PrePos = position;


	//画像の読み込み
	image.Create((std::string)"MissionUI.png");
	this->SetDrawOrder(0.1f);


	return true;
}
bool MissionUI::Finalize()
{
	image.Finalize();
	return true;
}
void MissionUI::EasingMove()
{
	if(easingX.isplay())
	{
		position.x = easingX.quint.Out(10, 0, this->PrePos.x, easingX.Time(10));
	}
}
void MissionUI::UpDate()
{
	this->EasingMove();
}
void MissionUI::Render2D()
{
	Box2D draw(position, Scale);
	draw.OffsetSize();
	Box2D src = this->Src;
	src.OffsetSize();
	image.Draw(draw, src);
}
MissionUI::MissionUI()
{
	std::cout << "ミッションUI　生成" << std::endl;
}
MissionUI::~MissionUI()
{
	this->Finalize();
	std::cout << "ミッションUI　解放" << std::endl;
}
MissionUI::SP MissionUI::Create(Vec2& pos, bool flag)
{
	MissionUI::SP to = MissionUI::SP(new MissionUI());
	if (to)
	{
		to->me = to;
		if (flag)
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