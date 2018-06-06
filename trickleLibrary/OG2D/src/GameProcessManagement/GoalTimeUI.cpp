#include "GoalTimeUI.h"
bool GoalTimeUI::Initialize(Vec2& pos)
{
	//タスク関連
	this->taskName = "GoalTimeUI";
	this->Init(taskName);

	//基本の情報
	CreateObject(Cube, pos, Vec2(448, 90), 0);
	

	//画像関連
	image.Create((std::string)"TimeUI.png");
	this->SetDrawOrder(0.1f);
	this->ResetVolume();

	//Easing関連
	this->PrePos = position;
	this->easingX.ResetTime();
	this->easingX.Init();
	this->easingEnd = false;

	std::cout << "ゴールタイムUI　初期化" << std::endl;
	return true;
}
void GoalTimeUI::ResetVolume()
{
	this->Volume = 0;
}
bool GoalTimeUI::Finalize()
{
	image.Finalize();
	return true;
}
void GoalTimeUI::UpDate()
{
	this->MoveVolume();
}
void GoalTimeUI::MoveVolume()
{
	this->Volume += 0.02f;
	if (this->Volume >= 1.0f)
	{
		this->Volume = 1.0f;
	}
}
void GoalTimeUI::Render2D()
{
	Box2D draw(position.x , (position.y + Scale.y) - (Scale.y * (this->Volume / 1.0f)), Scale.x , Scale.y * (this->Volume / 1.0f));
	draw.OffsetSize();
	Box2D src = this->Src;
	src.y = src.y * (src.y * this->Volume);
	src.OffsetSize();
	image.Draw(draw,src);
}
bool GoalTimeUI::GetEasingEnd()
{
	return easingEnd;
}
GoalTimeUI::GoalTimeUI()
{
	std::cout << "ゴールタイムUI　生成" << std::endl;
}
GoalTimeUI::~GoalTimeUI()
{
	this->Finalize();
	std::cout << "ゴールタイムUI　解放" << std::endl;
}
GoalTimeUI::SP GoalTimeUI::Create(Vec2& pos, bool flag)
{
	GoalTimeUI::SP to = GoalTimeUI::SP(new GoalTimeUI());
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