#include "MissionUI.h"
bool MissionUI::Initialize()
{
	this->taskName = "MissionUI";
	this->Init(taskName);
	std::cout << "ミッションUI　初期化" << std::endl;

	//Easing設定
	easingY.Init();
	easingY.ResetTime();

	Vec2 camerasize = OGge->camera->GetSize();
	CreateObject(Cube, Vec2((int)camerasize.x / 2 - 200,0), Vec2(512, 64), 0);


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
	Vec2 camerasize = OGge->camera->GetSize();

	if(easingY.isplay())
	{
		//上から下
		position.y = easingY.quint.Out(10, camerasize.y / 100 * 80  , -camerasize.y / 100 * 80 + 30 , easingY.Time(10));
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
MissionUI::SP MissionUI::Create(bool flag)
{
	MissionUI::SP to = MissionUI::SP(new MissionUI());
	if (to)
	{
		to->me = to;
		if (flag)
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