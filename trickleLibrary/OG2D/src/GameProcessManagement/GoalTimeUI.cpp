#include "GoalTimeUI.h"
bool GoalTimeUI::Initialize(Vec2& pos)
{
	this->taskName = "GoalTimeUI";
	this->Init(taskName);
	std::cout << "ゴールタイムUI　初期化" << std::endl;

	CreateObject(Cube, pos, Vec2(448, 90), 0);
	this->SetDrawOrder(0.1f);
	image.Create((std::string)"TimeUI.png");
	return true;
}
bool GoalTimeUI::Finalize()
{
	image.Finalize();
	return true;
}
void GoalTimeUI::UpDate()
{

}
void GoalTimeUI::Render2D()
{
	Box2D draw(position, Scale);
	draw.OffsetSize();
	Box2D src = this->Src;
	src.OffsetSize();
	image.Draw(draw,src);
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